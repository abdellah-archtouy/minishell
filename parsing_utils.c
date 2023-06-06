#include "mini.h"

int strlen_q(char *input)
{
    int i = 0;
    int j = 0;
    while (input[i])
    {
        if(input[i] == '\'')
        {
            i++;
            while (input[i] != '\'')
            {
                i++;
                j++;
            }
            if (input[i] == '\'')
                i++;
            continue ;
        }
        else if(input[i] == '\"')
        {
            i++;
            while (input[i] != '\"')
            {
                i++;
                j++;
            }
            if (input[i] == '\"')
                i++;
            continue ;
        }
        j++;
        i++;
    }
    return (j);
}

char    *quotes_remover(char *input)
{
    int    i;
    int    j;
    char *str;

    i = 0;
    j = 0;
    str = malloc(strlen_q(input) + 1);
    while (input[i])
    {
        if (input[i] != '\"' && input[i] != '\'' && input[i])
            str[j++] = input[i++];
        if (input[i] == '\"' && input[i])
        {
            i++;
            while (input[i] != '\"' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\"')
                i++;
        }
        if (input[i] == '\'' && input[i])
        {
            i++;
            while (input[i] != '\'' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\'')
                i++;
        }
    }
    str[j] = 0;
    return (str);
}
