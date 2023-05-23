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

int	ft_getfile(char *input)
{
	int	j = 0;
	char	*file = NULL;

	// i++;
	// while (input[i] == ' ')
	// 	i++;
	// while (input[i] != ' ')
	// {
	// 	file[j] = input[i];
	// 	i++;
	// 	j++;
	// }
	// file[j] = '\0';
	int fd = open(input, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("Error: open\n");
		exit(1);
	}
	return (fd);
}

// void	rev_char(char *input) // mokhawarton
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			while (input[i] && (input[i] == '\'' || input[i] == '"'))
// 				i++;
// 			while (input[i] && (input[i] != '\'' && input[i] != '"'))
// 				input[i++] *= -1;
// 		}
// 		i++;
// 	}
// }

// int ft_strcmp(const char *a, const char *b)
// {
// 	unsigned char *s1;
// 	unsigned char *s2;
// 	size_t i;

// 	i = 0;
// 	s1 = (unsigned char *)a;
// 	s2 = (unsigned char *)b;

// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	if ((s1[i] - s2[i]) == 0)
// 		return (0);
// 	else if ((s1[i] - s2[i]) > 0)
// 		return (1);
// 	else
// 		return (-1);
// }
// void lexer(char **str, t_list **ptr)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_strcmp(str[i], "<") == 0)
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], RINPUT));
// 		else if (ft_strcmp(str[i], ">") == 0)
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], ROUTPUT));
// 		else if (ft_strcmp(str[i], ">>") == 0)
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], APAND));
// 		else if (ft_strcmp(str[i], "<<") == 0)
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], HEREDOC));
// 		else if (ft_strcmp(str[i], "|") == 0)
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], PIPE));
// 		else
// 			ft_lstadd_back(ptr, ft_lstnew(str[i], WORD));
// 		i++;
// 	}
// }

// int	is_special(char c)
// {
// 	return(c == '|' || c == '>' || c == '<');
// }

// char	*tkhwira(char *input)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *str;

// 	str = malloc(ft_strlen(input) * 2);
// 	while (input[i])
// 	{
// 		if (input[i] && input[i] == '\'')
// 		{
// 			str[j++] = input[i++];
// 			while (input[i] && input[i] != '\'')
// 				str[j++] = input[i++];
// 			str[j++] = input[i];
// 		}
// 		else if (input[i] && input[i] == '\"')
// 		{
// 			str[j++] = input[i++];
// 			while (input[i] && input[i] != '\"')
// 				str[j++] = input[i++];
// 			str[j++] = input[i];
// 		}
// 		else if (input[i] && is_special(input[i]))
// 		{
// 			str[j++] = ' ';
// 			if (input[i] == input[i + 1])
// 				str[j++] = input[i++];
// 			str[j++] = input[i];
// 			str[j++] = ' ';
// 		}
// 		else
// 			str[j++] = input[i];
// 		i++;
// 	}
// 	str[j] = 0;
// 	return (str);
// }

int main(int ac , char **av)
{
	// int i = 0;
	// char *input = strdup("\"\" \"\" \"\" \"\" \"\" \"\"  |  ahlan  |  hello");
	// char **input1;
	// t_list *ptr;

	// ptr = NULL;
	// rev_char(input);
	// input1 = ft_split(tkhwira(input));
	// while (input1[i])
	// 	rev_char(input1[i++]);
	// lexer(input1, &ptr);
	// while (ptr)
	// {
	// 	printf("str %s --- type %d\n", ptr->content, ptr->type);
	// 	ptr = ptr->next;
	// }

	int j = 0;
	int fd = ft_getfile(av[1]);
	printf("%d\n", fd);
	while (av[2][j])
	{
		write(fd, &av[2][j], 1);
		j++;
	}
	
	// printf("%s\n", tkhwira(input));
}


////////////////////////////     old syntaxe error      ////////////////////////////////////


// int	ft_help2(char *input, int *i)
// {
// 	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
// 				(*i)++;
// 	if (input[*i] == '\0')
// 		return (1);
// 	return (0);
// }

// int	ft_help_check(char *input, int *i)
// {
// 	if (input[*i] == '<')
// 	{
// 		(*i)++;
// 		if (input[*i] == '<')
// 		{
// 			(*i)++;
// 			while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
// 				(*i)++;
// 			if (is_special(input[*i]))
// 				return (1);
// 		}
// 	}
// 	if (input[*i] == '>')
// 	{
// 		(*i)++;
// 		if (input[*i] == '>')
// 		{
// 			(*i)++;
// 			while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
// 				(*i)++;
// 			if (is_special(input[*i]))
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// int	ft_check_helper1(char *input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_help_check(input, &i))
// 			return (1);
// 		else if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<')
// 			|| (input[i] == '>' && input[i + 1] != '>'))
// 		{
// 			i++;
// 			if (ft_help2(input, &i))
// 				return (1);
// 		}
// 		else if ((input[i] == '<' && input[i + 1] == '<')
// 			|| (input[i] == '>' && input[i + 1] == '>'))
// 		{
// 			i += 2;
// 			if (ft_help2(input, &i))
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_help(char *input, int *i, char c)
// {
// 	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
// 				(*i)++;
// 	if (is_special(input[*i]) && input[*i] != c)
// 		return (1);
// 	return (0);
// }

// int	ft_check_helper(char *input, int i)
// {
// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 		{
// 			i++;
// 			if (ft_help(input, &i, 0))
// 				return (1);
// 		}
// 		else if (input[i] == '<')
// 		{
// 			i++;
// 			if (ft_help(input, &i, '<'))
// 				return (1);
// 		}
// 		else if (input[i] == '>')
// 		{
// 			i++;
// 			if (ft_help(input, &i, '>'))
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	check_syntaxe(char	*input)
// {
// 	int	i;

// 	i = 0;
// 	rev_char(input);
// 	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 		i++;
// 	if (input[i] == '<')
// 	{
// 		i++;
// 		if (input[i] == '<')
// 		{
// 			i++;
// 			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 				i++;
// 			if (is_special(input[i]))
// 				return (1);
// 		}
// 	}
// 	else if (ft_check_helper(input, i) || ft_check_helper1(input))
// 		return (1);
// 	rev_char(input);
// 	return (0);
// }
