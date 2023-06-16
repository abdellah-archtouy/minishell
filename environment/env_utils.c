/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:24 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/15 20:56:50 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	is_sorted(t_env *exp)
{
	while (exp->next != NULL)
	{
		if (ft_strcmp(exp->key, exp->next->key) > 0)
			return (0);
		exp = exp->next;
	}
	return (1);
}

void	swap_nodes(t_env **tmp)
{
	int		i;
	char	*a;

	i = 0;
	a = (*tmp)->key;
	(*tmp)->key = (*tmp)->next->key;
	(*tmp)->next->key = a;
	a = (*tmp)->content;
	(*tmp)->content = (*tmp)->next->content;
	(*tmp)->next->content = a;
	i = (*tmp)->flag;
	(*tmp)->flag = (*tmp)->next->flag;
	(*tmp)->next->flag = i;
}

int	node_existences(t_env *env, char *key)
{
	int	i;

	i = 0;
	if (ft_strchr(key, '+'))
	{
		i = ft_strlen(key) - 1;
		while (env != NULL)
		{
			if (ft_strncmp(env->key, key, i) == 0)
				return (0);
			env = env->next;
		}
	}
	else
	{
		while (env != NULL)
		{
			if (ft_strcmp(env->key, key) == 0)
				return (0);
			env = env->next;
		}
	}
	return (1);
}

void	update_shell_level(char **content, int r)
{
	int	l;

	l = ft_atoi(*content);
	if (*content == 0)
		*content = ft_strdup("1");
	else if (l == 999)
	{
		free(*content);
		(*content) = strdup("");
	}
	else if (l < 0 && r == 0)
	{
		free(*content);
		*content = ft_strdup("0");
	}
	else
	{
		free(*content);
		*content = ft_itoa(l + 1);
	}
}

void	get_key(char *string, char **returned, char *found)
{
	int		size;
	int		i;

	i = 0;
	if (found != NULL)
	{
		size = found - string;
		*returned = malloc(size + 1);
		while (string[i] && string[i] != '=')
		{
			(*returned)[i] = string[i];
			i++;
		}
		(*returned)[i] = 0;
	}
	else
		*returned = ft_strdup(string);
}
