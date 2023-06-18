/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:37 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 18:31:09 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_env	*sorted_env(t_env *exp)
{
	t_env	*tmp;
	t_env	*save;

	tmp = copy_list(exp);
	save = tmp;
	while (is_sorted(save) == 0)
	{
		tmp = save;
		while (tmp->next != NULL)
		{
			if ((ft_strcmp(tmp->key, tmp->next->key) > 0))
				swap_nodes(&tmp);
			tmp = tmp->next;
		}
	}
	return (save);
}

void	lst_clear_env(t_env *env)
{
	t_env	*head;

	while (env != NULL)
	{
		head = env->next;
		free(env);
		env = head;
	}
	env = NULL;
}

void	unset_clear_node(t_env **h)
{
	if (((*h)->key))
		free((*h)->key);
	if (((*h)->content))
		free((*h)->content);
	free((*h));
}

void	unset_helper(t_env *head, t_env *head0, t_env **env)
{
	if (head == *env)
	{
		head = (*env)->next;
		unset_clear_node(env);
		*env = head;
	}
	else
	{
		while (head0->next != NULL && head != *env)
		{
			if (head0->next == head)
			{
				head0->next = head->next;
				unset_clear_node(&head);
				break ;
			}
			head0 = head0->next;
		}
	}
}

void	unset(t_env **env, char **str)
{
	int		i;
	int		j;
	t_env	*head;
	t_env	*head0;

	i = 1;
	j = 0;
	head = *env;
	head0 = *env;
	while (str && str[i])
	{
		head0 = *env;
		if (parsing(str[i], *env) || node_existences(*env, str[i])
			|| (ft_strchr(str[i], '=') && ft_strlen(str[i]) == 1))
		{
			if (parsing(str[i], *env)
				|| (ft_strchr(str[i], '=') && ft_strlen(str[i]) == 1))
				print_unset_error(str[i], 1);
			i++;
			continue ;
		}
		head = lstch_env(*env, str[i]);
		unset_helper(head, head0, env);
		i++;
	}
}
