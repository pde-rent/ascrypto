#include "ascrypto.h"

void    reseed(void)
{
    srand(time(NULL));//how the fuck do we seed rnd to time??
}

char     rnd_ascii(void)
{
    //return rand char in dec interval [33;126]
    return ((char)(33 + (rand()/(RAND_MAX/94))));
}

int     roll(int max)
{
    int coef = RAND_MAX / max;
    //reseed(); //how the fuck do we seed rnd to time??
    return (rand()/(coef));
}

char     shuffle(int c)
{
    //return rand char in dec interval [33;79] or [79;126] opposite to current dec side
    int tmp;
    int sum;
    tmp = ((c >= 79) ? (c - roll(47)) : (c + roll(47)));
    sum = ((c >= tmp) ? (c - tmp) : (tmp - c));
//    printf("%d & %d = %d\n", c, tmp, sum);
    if ((sum > 126) || (sum < 33))
        return (shuffle(c));
    return(tmp);
}

char    *splitter(void)
{
    //the splitter is a chain of 3 characters counting for 316 overall ascii dec, starting and ending with a lowercase
    char *str = (char *)malloc(sizeof(char) * 4);

    str[0] = 97 + roll(25);
    str[2] = 97 + roll(25);
    str[1] = 316 - (str[0] + str[2]);
    str[3] = '\0';
    return (str);
}

int     pos_splitter(char *str)
{
    int i;

    if (!(str))
        return (-1);
    for (i = ((int)strlen(str) / 4) - 3; i <= (int)strlen(str); i++)
    {
//        printf("%d\n", (str[i] + str[i + 1] + str[i + 2]));
        if ((str[i] + str[i + 1] + str[i + 2]) == 316)
            if (str[i] >= 'a' && str[i] <= 'z')
                if (str[i + 2] >= 'a' && str[i + 2] <= 'z')
                        return (i);
    }
    return (-1);
}