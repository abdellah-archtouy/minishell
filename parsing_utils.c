/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:54:35 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 20:48:04 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_qout(char *input, int *i)
{
	char	*str;
	char	*str1;

	str = ft_strdup("");
	str1 = ft_get_char(NULL, input[*i]);
	str = ft_strjoin(str, str1);
	free(str1);
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		str1 = ft_get_char(NULL, input[*i]);
		str = ft_strjoin(str, str1);
		free(str1);
		(*i)++;
	}
	str1 = ft_get_char(NULL, input[*i]);
	str = ft_strjoin(str, str1);
	free(str1);
	if (input[*i] != '\0')
		(*i)++;
	return (str);
}

void	strlen_q_h1(int *i, int *j, char *input, char c)
{
	(*i)++;
	while (input[(*i)] != c)
	{
		(*i)++;
		(*j)++;
	}
	if (input[(*i)] == c)
		(*i)++;
}

int	strlen_q(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			strlen_q_h1(&i, &j, input, '\'');
			continue ;
		}
		else if (input[i] == '\"')
		{
			strlen_q_h1(&i, &j, input, '\"');
			continue ;
		}
		j++;
		i++;
	}
	return (j);
}

void	quotes_remover_h(int *i, int *j, char *input, char **str)
{
	if (input[*i] != '\"' && input[*i] != '\'' && input[*i])
		(*str)[(*j)++] = input[(*i)++];
	if (input[*i] == '\"' && input[*i])
	{
		(*i)++;
		while (input[*i] != '\"' && input[*i])
			(*str)[(*j)++] = input[(*i)++];
		if (input[*i] == '\"')
			(*i)++;
	}
	if (input[*i] == '\'' && input[*i])
	{
		(*i)++;
		while (input[*i] != '\'' && input[*i])
			(*str)[(*j)++] = input[(*i)++];
		if (input[*i] == '\'')
			(*i)++;
	}
}

char	*quotes_remover(char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(strlen_q(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
		quotes_remover_h(&i, &j, input, &str);
	str[j] = 0;
	free(input);
	return (str);
}
