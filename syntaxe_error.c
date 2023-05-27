#include "mini.h"

int	pipe_syntaxe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (is_special(input[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	rin_syntaxe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			i++;
			if (input[i] == '<')
			{
				i++;
				while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
					i++;
				if (input[i] == '\0')
					return (1);
			}
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (is_special(input[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	rout_syntaxe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				i++;
			while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
				i++;
			if (is_special(input[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	start_and_end(char *input) // ( )
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(input) - 1;
	while ((input[j] >= 9 && input[j] <= 13) || input[j] == ' ')
		j--;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (is_special(input[j]) || input[j] == ')' || input[j] == '(')
		return (1);
	if ((is_special(input[i]) && input[i] != '<' && input[i] != '>')
		|| input[i] == ')' || input[i] == '(')
		return (1);
	return (0);
}

int	syntaxe_error(char *input)
{
	rev_char(input);
	if (start_and_end(input))
		return (1);
	if (pipe_syntaxe(input))
		return (1);
	if (rin_syntaxe(input))
		return (1);
	if (rout_syntaxe(input))
		return (1);
	rev_char(input);
	return (0);
}
