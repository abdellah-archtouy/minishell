
#include "mini.h"

int	ft_help2(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
				(*i)++;
	if (input[*i] == '\0')
		return (1);
	return (0);
}

int	ft_help_check(char *input, int *i)
{
	if (input[*i] == '<')
	{
		(*i)++;
		if (input[*i] == '<')
		{
			(*i)++;
			while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
				(*i)++;
			if (is_special(input[*i]))
				return (1);
		}
	}
	if (input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == '>')
		{
			(*i)++;
			while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
				(*i)++;
			if (is_special(input[*i]))
				return (1);
		}
	}
	return (0);
}

int	ft_check_helper1(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		// if (input[i] == '<')
		// {
		// 	i++;
		// 	if (input[i] == '<')
		// 	{
		// 		i++;
		// 		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		// 			i++;
		// 		if (is_special(input[i]))
		// 			return (1);
		// 	}
		// }
		// if (input[i] == '>')
		// {
		// 	i++;
		// 	if (input[i] == '>')
		// 	{
		// 		i++;
		// 		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		// 			i++;
		// 		if (is_special(input[i]))
		// 			return (1);
		// 	}
		// }
		if (ft_help_check(input, &i))
			return (1);
		else if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<')
			|| (input[i] == '>' && input[i + 1] != '>'))
		{
			i++;
			if (ft_help2(input, &i))
				return (1);
		}
		else if ((input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
		{
			i += 2;
			if (ft_help2(input, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_help(char *input, int *i, char c)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
				(*i)++;
	if (is_special(input[*i]) && input[*i] != c)
		return (1);
	return (0);
}

int	ft_check_helper(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			if (ft_help(input, &i, 0))
				return (1);
		}
		else if (input[i] == '<')
		{
			i++;
			if (ft_help(input, &i, '<'))
				return (1);
		}
		else if (input[i] == '>')
		{
			i++;
			if (ft_help(input, &i, '>'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_syntaxe(char	*input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '<')
	{
		i++;
		if (input[i] == '<')
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (is_special(input[i]))
				return (1);
		}
	}
	else if (ft_check_helper(input, i) || ft_check_helper1(input))
		return (1);
	return (0);
}
