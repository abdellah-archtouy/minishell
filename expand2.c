/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:30 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 15:12:59 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*ft_get_char(char *str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	(void)str;
	str1 = malloc(2);
	if (!str1)
		return (NULL);
	str1[i++] = c;
	str1[i] = '\0';
	return (str1);
}
