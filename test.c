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

void	rev_char(char *input)
{
	int	i;

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

int	ft_strcmp(const char *a, const char *b)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)a;
	s2 = (unsigned char *)b;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if ((s1[i] - s2[i]) == 0)
		return (0);
	else if ((s1[i] - s2 [i]) > 0)
		return (1);
	else
		return (-1);
}
void	lexer(char	**str, t_list	**ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], RINPUT));
		else if (ft_strcmp(str[i], ">") == 0 )
			ft_lstadd_back(ptr, ft_lstnew(str[i], ROUTPUT));
		else if (ft_strcmp(str[i], ">>") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], APAND));
		else if (ft_strcmp(str[i], "<<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], HEREDOC));
		else if (ft_strcmp(str[i], "|") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], PIPE));
		else
			ft_lstadd_back(ptr, ft_lstnew(str[i], WORD));
		i++;
	}
}

int	main()
{
	char	*input = strdup("talal | miftah << >> | < dsu > vdav");
	char	**input1;
	t_list	*ptr;

	ptr = NULL;
	input1 = ft_split(input);
	lexer(input1, &ptr);
	while (ptr)
	{
		printf("str %s --- type %d\n", ptr->content, ptr->type);
		ptr = ptr->next;
	}
	// printf("%s\n", input);
}
