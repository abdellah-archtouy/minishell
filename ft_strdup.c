/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:17:28 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 15:14:18 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0)
	{
	d[i] = s[i];
		i++;
		n--;
	}
	return (d);
}

char	*ft_strdup(char *s1)
{
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*ptr;
	char	*tmp;
	int		index;

	tmp = (char *)s;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s) < len)
		len = ft_strlen(s);
	index = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (len && tmp[start])
	{
		ptr[index++] = tmp[start++];
		len--;
	}
	ptr[index] = '\0';
	return (ptr);
}

int	ft_strncmp( char *a, char *b, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)a;
	s2 = (unsigned char *)b;
	if (!a || !b)
		return (-1);
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
		i++;
	if ((s1[i] - s2[i]) == 0)
		return (0);
	else if ((s1[i] - s2[i]) > 0)
		return (1);
	else
		return (-1);
}
