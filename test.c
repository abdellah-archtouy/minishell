#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mini.h"

// int main() {
//     // fork();

//     // printf("current id %d || parent id %d\n", getpid(), getppid());
//     char **str = ft_split("\ttalal\tl3azwa", ' ');
//     printf("%s\n", str[0]);
//     printf("%s\n", str[1]);
//     return 0;
// }

void    rev_char(char *input)
{
    int    i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            i++;
            while (input[i] && (input[i] != '\'' && input[i] != '"'))
                input[i++] *= -1;
        }
        i++;
    }
}
int main() {
  char *input = strdup("\"talal\" \"miftah\"");
  rev_char(input);
  printf("%s\n", input);
}