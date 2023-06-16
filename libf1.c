/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libf1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:17:43 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/16 15:17:44 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*a;

	a = (void *)malloc(sizeof(t_list));
	if (a == 0)
		return (0);
	a->content = content;
	a->type = type;
	a->next = 0;
	a->flag = 0;
	return (a);
}

int	ft_strcmp(const char *a, const char *b)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)a;
	s2 = (unsigned char *)b;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if ((s1[i] - s2[i]) == 0)
		return (0);
	else if ((s1[i] - s2 [i]) > 0)
		return (1);
	else
		return (-1);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
