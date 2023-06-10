#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (input[i] == '\"' && input[i])
        {
            i++;
            while (input[i] != '\"' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\"')
                i++;
            continue ;
        }
        if (input[i] == '\'' && input[i])
        {
            i++;
            while (input[i] != '\'' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\'')
                i++;
            continue ;
        }
        i++;
    }
    str[j] = 0;
    return (str);
}

// int main(int ac, char **av) {
//     printf("%s\n", quotes_remover(av[1]));
//     return 0;
// }

#include <stdio.h>

int main() {
    const char *line = "Name: John Doe";

    // Find the position of the colon character
    const char *colon = strchr(line, ':');
    if (colon != NULL) {
        // Calculate the number of characters to skip (including the colon)
        int skipCount = colon - line + 1;

        // Print the line, skipping the specified number of characters
        printf("%*s\n", skipCount, "abdo");
    }

    return 0;
}
