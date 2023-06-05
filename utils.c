
#include "mini.h"

int	is_special(char c)
{
	return(c == '|' || c == '>' || c == '<');
}

char	*add_space(char *input)
{
	int i = 0;
	int j = 0;
	char *str;

	str = malloc(ft_strlen(input) * 2);
	while (input[i])
	{
		if (input[i] && input[i] == '\'')
		{
			str[j++] = input[i++];
			while (input[i] && input[i] != '\'')
				str[j++] = input[i++];
			str[j++] = input[i];
		}
		else if (input[i] && input[i] == '\"')
		{
			str[j++] = input[i++];
			while (input[i] && input[i] != '\"')
				str[j++] = input[i++];
			str[j++] = input[i];
		}
		else if (input[i] && is_special(input[i]))
		{
			str[j++] = ' ';
			if (input[i] == input[i + 1])
				str[j++] = input[i++];
			str[j++] = input[i];
			str[j++] = ' ';
		}
		else
			str[j++] = input[i];
		i++;
	}
	str[j] = 0;
	// free(input);
	return (str);
}

int strlen_q(char *input)
{
	int i = 0;
	int j = 0;
	while (input[i])
	{
		if (input[i] == '\'')
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
		else if (input[i] == '\"')
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

char	*quotes_remover(char *input)
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
	if (j == 0)
		return (input);
	str[j] = 0;
	free(input);
	return (str);
}
