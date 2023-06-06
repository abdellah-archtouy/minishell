#include "mini.h"

int	dollar_exist(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		if (input[i++] == '$')
			return (1);
	return (0);
}

char	*single_quote(char *input)
{
	char	*str;
	int		r;
	int		i;

	r = 0;
	i = 0;
	str = malloc(ft_strlen(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] != '\'')
		{
			str[r] = input[i];
			r++;
		}
		i++;
	}
	str[r] = 0;
	return (str);
}

char	*double_quote(char *input)
{
	int		r;
	int		i;
	char	*str;

	r = 0;
	i = 0;
	str = malloc(ft_strlen(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] != '\"')
		{
			str[r] = input[i];
			r++;
		}
		i++;
	}
	str[r] = 0;
	return (str);
}

void	fd(char **input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '\'' || input[i][j] == '\"')
			{
				if (input[i][j] == '\'')
					str = single_quote(input[i]);
				else if (input[i][j] == '\"')
					str = double_quote(input[i]);
				free(input[i]);
				input[i] = str;
				break ;
			}
			j++;
		}
		i++;
	}
}
