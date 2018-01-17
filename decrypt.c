#include "ascrypto.h"

void    decrypt_str(char *pubkey, char *prikey, char *output_file)
{
    int pri_len = (int)strlen(prikey);
    int output_len = pri_len / 3;
    char *output;
    int sign;
    int i = 0;
    int j = output_len;
    int k = (pri_len / 3) * 2;
    int l = 0;
    int x = j;
    int shift = -1;

    output = (char *)malloc(sizeof(char) * (output_len + 1));
    while (--x > -1)
    {
        shift += (prikey[j] - '0' + 1);
        sign = (prikey[k] > 79 ? 1 : -1);
//        printf("\nshift:  %d\npubkey[shift]:  %d\nprikey[i]: %d\nletter:  %d\n", shift, pubkey[shift], prikey[i], (pubkey[shift] + prikey[i] * sign));
        output[l] = pubkey[shift] + prikey[i] * sign;
        i++; j++; k++; l++;
    }
    while (++l < (output_len + 1))
        output[l] = '\0';
//    printf("Public key:  %s\nPrivate key: " FRED "%s\n" FNONE "Decrypt: " FGREEN ">>> %s\n" FNONE, pubkey, prikey, output);
    printf("Public key:  %s\nPrivate key: %s\nDecrypt: >>> %s\n", pubkey, prikey, output);
    str_to_file(output, output_file);
    free(pubkey);
    free(prikey);
}

void    decrypt_file(char *input_file, char *output_file)
{
    char *str;
    int i = -1;
    int j = -1;
    int split;
    int len;
    char *pubkey;
    char *prikey;

    str = file_to_str(input_file);
    //printf("Full input file: %s\n", (str));
    split = pos_splitter(str);
    len = strlen(str);
    free(str);
    if (!(split > 0) || !str)
    {
        printf("split error\n");
        return ;
    }
    pubkey = (char *)malloc(sizeof(char) * (split + 1));
    prikey = (char *)malloc(sizeof(char) * (strlen(str) - (split + 2)));
    while (++i < split)
        pubkey[i] = str[i];
    pubkey[++i] = '\0'; i++;
    while (++i < (int)strlen(str))
        prikey[++j] = str[i];
    printf("prikey before passing: \n%s", prikey);
    decrypt_str(pubkey, prikey, output_file);
}

void    depth_decrypt(char *input_file, int depth, char *output_file)
{
    if (depth)
        while (--depth >= 0)
            decrypt_file(input_file, input_file);
    decrypt_file(input_file, output_file);
}

int     main(int ac, char **av)
{
    int depth = atoi(av[2]);
    char *input_file = (av[1]);
    char *output_file = (av[3]);
    depth_decrypt(input_file, depth, output_file);
    return 0;
}