/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:31 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/15 20:55:32 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_env	*ft_lstnew_env(char *key, char *content)
{
	t_env	*a;

	a = (void *)malloc(sizeof(t_env));
	if (!a)
		return (0);
	a->content = content;
	a->key = key;
	a->flag = 0;
	a->next = NULL;
	return (a);
}

int	ft_lstsize_env(t_env *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	ft_lstlast_env(*lst)->next = new;
}

t_env	*lstch_env(t_env *head, char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			break ;
		head = head->next;
	}
	return (head);
}
