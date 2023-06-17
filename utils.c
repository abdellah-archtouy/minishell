/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:38:20 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 15:15:28 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_special(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

void	add_space1(int *i, int *j, char *str, char *input)
{
	if (input[(*i)] && input[(*i)] == '\'')
	{
		str[(*j)++] = input[(*i)++];
		while (input[(*i)] && input[(*i)] != '\'')
			str[(*j)++] = input[(*i)++];
		str[(*j)++] = input[(*i)];
	}
	else if (input[(*i)] && input[(*i)] == '\"')
	{
		str[(*j)++] = input[(*i)++];
		while (input[(*i)] && input[(*i)] != '\"')
			str[(*j)++] = input[(*i)++];
		str[(*j)++] = input[(*i)];
	}
	else if (input[(*i)] && is_special(input[(*i)]))
	{
		str[(*j)++] = ' ';
		if (input[(*i)] == input[(*i) + 1])
			str[(*j)++] = input[(*i)++];
		str[(*j)++] = input[(*i)];
		str[(*j)++] = ' ';
	}
	else
		str[(*j)++] = input[(*i)];
}

char	*add_space(char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(input) * 2);
	if (!str)
		return (NULL);
	while (input[i])
	{
		add_space1(&i, &j, str, input);
		i++;
	}
	str[j] = 0;
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
