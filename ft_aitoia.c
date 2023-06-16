/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aitoia.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:44:09 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/16 15:16:00 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	int_count(int i)
{
	int	r;

	r = 0;
	if (i <= 0)
		r = 1;
	while (i != 0)
	{
		i = i / 10;
		r++;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		ln;
	long	result;

	i = 0;
	result = n;
	ln = int_count(n);
	s = malloc(ln + 1);
	if (!s)
		return (NULL);
	if (result < 0)
	{
		result *= -1;
		s[i] = '-';
		i++;
	}
	s[ln] = '\0';
	while (ln > i)
	{
		s[ln - 1] = (result % 10) + '0';
		result = result / 10;
		ln--;
	}
	return (s);
}

char	*ft_strchr(char *s, int c)
{
	char	*c1;

	c1 = (char *)s;
	while (*c1 != '\0')
	{
		if (*c1 == (char)c)
			return (c1);
		c1++;
	}
	if (*c1 == '\0' && *c1 == (char)c)
		return (c1);
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	int		ssize;
	int		r;
	char	*c1;

	ssize = ft_strlen(s);
	c1 = (char *)s;
	r = 0;
	while (ssize >= 0)
	{
		if (c1[ssize] == (char)c)
			return (c1 + ssize);
		else
			ssize--;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result *= 10;
		result += (*str - '0');
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		else if (result > 9223372036854775807)
			return (-1);
		str++;
	}
	return (result * sign);
}
