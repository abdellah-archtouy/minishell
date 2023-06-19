/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:12:47 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 18:15:12 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_parc_norm1(t_list **ptr, int i)
{
	if (i == 0)
	{
		while ((*ptr) && (*ptr)->type != PIPE)
		{
			free((*ptr)->content);
			free((*ptr));
			(*ptr) = (*ptr)->next;
		}
	}
	if (i == 1)
	{
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
}

void	ft_parc_norm2(t_list **ptr, int *i, char ***str, char ***str1)
{
	int	a;

	if ((*ptr)->flag == 0)
	{
		a = 0;
		(*str1) = ft_split((*ptr)->content);
		while ((*str1)[a] != NULL)
			(*str)[(*i)++] = (*str1)[a++];
		free((*str1));
	}
	else
		(*str)[(*i)++] = ft_strdup((*ptr)->content);
}

int	ft_word_count(t_list *head)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			if (head->flag == 0)
				ft_word_count_helper(head->content, &a, &i);
			else
				i++;
		}
		head = head->next;
	}
	return (i);
}

void	function(int r, t_env **head, char **env)
{
	int	i;

	i = 0;
	if (r > 0)
	{
		lstch_env(*head, "PATH")->flag = 1;
		while (env[i])
			free(env[i++]);
		free(env);
	}
	lstadd_back_env(head, ft_lstnew_env(ft_strdup("?"), ft_strdup("0")));
	if (!lstch_env(*head, "OLDPWD"))
		lstadd_back_env(head, ft_lstnew_env(ft_strdup("OLDPWD"), NULL));
}
