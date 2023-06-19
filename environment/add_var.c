/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:06 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 15:10:17 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	equal_num(char *input)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		if (input[i] == '-')
			return (1);
		if (input[i] == '+')
			p++;
		i++;
	}
	if (p > 1)
		return (1);
	return (0);
}

int	parsing(char *input, t_env *env)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=')
	{
		if (equal_num(input))
			return (1);
		if (ft_isalpha(input[0]) == 0)
			return (1);
		while (input[i] && input[i] != '=')
		{
			if (ft_isalpha(input[i])
				|| (input[i] == '+' && ft_strchr(input, '='))
				|| (input[i] >= '0' && input[i] <= '9'))
				i++;
			else
			{
				if (lstch_env(env, "?")->content)
					free(lstch_env(env, "?")->content);
				lstch_env(env, "?")->content = ft_itoa(1);
				return (1);
			}
		}
	}
	return (0);
}

void	add_var_helper(char *key, char *content, t_env **env)
{
	t_env	*head;

	head = *env;
	if (ft_strchr(key, '+') == 0)
	{
		head = lstch_env(*env, key);
		free(key);
		free(head->content);
		head->content = content;
	}
	else if (ft_strchr(key, '+'))
	{
		while (head != NULL)
		{
			if (ft_strncmp(head->key, key, ft_strlen(key) - 1) == 0)
				break ;
			head = head->next;
		}
		free(key);
		head->content = ft_strjoin_ex(head->content, content);
		free(content);
	}
}

void	add_noexisted_var(char **key, char **content, t_env **env)
{
	if (ft_strchr(*key, '+'))
		(*key)[ft_strlen(*key) - 1] = '\0';
	lstadd_back_env(env, ft_lstnew_env(*key, *content));
}

void	add_var(t_env **env, char **str, int i)
{
	char	*content;
	char	*key;
	t_env	*head;

	head = *env;
	while (str[i])
	{
		key = get_chars(str[i], 0);
		content = get_chars(str[i], 1);
		if (parsing(str[i], *env) || ft_strlen(key) == 0)
		{
			add_var_norm(content, key);
			print_env_error(str[i], 0);
			exit_stat_update(env, 1);
			i++;
			continue ;
		}
		if (node_existences(*env, key))
			add_noexisted_var(&key, &content, env);
		else if (node_existences(*env, key) == 0 && content != NULL)
			add_var_helper(key, content, env);
		else if (node_existences(*env, key) == 0 && !content)
			free(key);
		i++;
	}
}
