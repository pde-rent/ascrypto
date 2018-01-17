#include "ascrypto.h"

void    encrypt_str(char *input_file, int difficulty, int depth, char *output_file)
{
    char *str;
    int i = -1;
    int j = -1;
    int k = -1;
    int len;
    int tmp;
    int cnt;
    char *split;
    char *pubkey;
    char *prikey;
    char *output;
    char *pripart[3];

    reseed();
    str = file_to_str(input_file);
    len = (int)strlen(str);
    pubkey = (char *)malloc(sizeof(char) * (len * (difficulty + 1) + 1));
    prikey = (char *)malloc(sizeof(char) * (len * (3) + 2));
    for (cnt = 0; cnt < 3; cnt++)
        pripart[cnt] = (char *)malloc(sizeof(char) * (len + 1));
    while (str[++i])
    {
        tmp = roll(difficulty);
        pripart[0][++k] = (char)(tmp + '0'); //goes up to difficulty 9, a good thing would be to go up all cases > 61 levels
        while ((--tmp > - 1))
            pubkey[++j] = rnd_ascii();
        pubkey[++j] = shuffle((int)str[i]);
        pripart[1][k] = (((int)pubkey[j] > (int)str[i]) ? shuffle(79) : shuffle(78));
        //putchar(pripart[1][k]);
        //putchar('\n');
        //printf("pubkey: %d><%d :str | %c\n", (int)pubkey[j], (int)str[i], prikey[k]);
        pripart[2][k] = (str[i] > 79) ? (str[i] - pubkey[j]) : (pubkey[j] - str[i]);
        //printf("pubkey(j):%c(%d)\nstr(i):%c(%d)\ndiff(k):%c(%d)\n", pubkey[j], pubkey[j], str[i], str[i], prikey[k], prikey[k]);
    }
    for (cnt = 0; cnt < 3; cnt++)
    {
        tmp = k;
        while (pripart[cnt][++tmp])
            pripart[cnt][tmp] = '\0';
    }
    while (pubkey[++j])
        pubkey[j] = '\0';
    //catenate all pripart into prikey
    prikey = strcpy(prikey, pripart[2]);
    strcat(prikey, pripart[0]);
    strcat(prikey, pripart[1]);
    printf("pripart 1:   %s\npripart 2:   %s\npripart 3:   %s\n", pripart[0], pripart[1], pripart[2]);
    printf("pubkey: %s\n",pubkey);
    split = splitter();
    printf("split: %s\n",split);
    output = (char *)malloc(sizeof(char) * (strlen(pubkey) + strlen(prikey) + (int)strlen(split) + 1));
    strcpy(output, pubkey);
    strcat(output, split);
    strcat(output, prikey);
    //printf("Full output: %s\n", output);
    str_to_file(output, output_file);
    //printf("pripart 1:   %s\npripart 2:   %s\npripart 3:   %s\n", pripart[0], pripart[1], pripart[2]);
    //printf("pubkey:   %s\n", pubkey);
    //printf("Input:       %s\nDifficulty:  %d\nDepth:       %d\nPublic Key:  %s\nPrivate Key: %s\nSplitter:    %s\n",
    //       str, difficulty, depth, pubkey, prikey, split);
    for (cnt = 0; cnt < 3; cnt++)
        free(pripart[cnt]);
    free(str);
    free(pubkey);
    free(prikey);
    free(split);
}

void    depth_encrypt(char *input_file, int difficulty, int depth, char *output_file)
{
    if (depth)
        while (--depth >= 0)
            encrypt_str(input_file, difficulty, depth + 1, input_file);
    encrypt_str(input_file, difficulty, 0, output_file);
}

int main(int ac, char **av)
{
    char *str = av[1];
    char *output_file = av[4];
    int difficulty = atoi(av[2]);
    int depth = atoi(av[3]);
    
    if (difficulty < 1)
    {
        printf("Difficulty can't be under 1\n");
        return 0;
    }
    if (difficulty > 9)
    {
        printf("Difficulty set to 9 (max)\n");
        difficulty = 9;
    }
    if (depth < 0)
    {
        printf("Encryption depth can't be negative\n");
        return 0;
    }
    if (depth > 5)
    {
        printf("Depth set to 5 (max)\n");
        depth = 5;
    }
    depth_encrypt(str, difficulty, depth, output_file);
    return 0;
}