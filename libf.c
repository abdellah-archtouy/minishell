/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:31:44 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/21 18:11:58 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == 0 || del == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del (lst->content);
	free (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*a;

	a = (void *)malloc(sizeof(t_list));
	if (a == 0)
		return (0);
	a->content = content;
	a->type = type;
	a->next = 0;
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}