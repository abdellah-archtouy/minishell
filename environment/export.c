/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:56 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/15 20:55:57 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	get_content(char *string, char **returned, char *found)
{
	int		size;
	int		i;
	int		j;

	i = 0;
	size = &string[ft_strlen(string) - 1] - found;
	j = ft_strlen(string) - size - 1;
	if (string[j] == '=')
		j++;
	(*returned) = malloc(size + 1);
	while (string[j])
	{
		(*returned)[i] = string[j];
		i++;
		j++;
	}
	(*returned)[i] = 0;
}

char	*get_chars(char *string, int index)
{
	char	*found;
	char	*returned;

	returned = NULL;
	found = ft_strchr(string, '=');
	if (index == 0)
		get_key(string, &returned, found);
	else if (index == 1 && found != NULL)
		get_content(string, &returned, found);
	return (returned);
}

void	print_env(t_parc *parc, t_env *head, int index)
{
	if (index == 0 && head->flag == 0)
	{
		ft_putstr_fd(head->key, parc->out);
		ft_putstr_fd("=", parc->out);
		ft_putstr_fd(head->content, parc->out);
		ft_putstr_fd("\n", parc->out);
	}
	else if (index == 1 && head->flag == 0)
	{
		ft_putstr_fd("declare -x ", parc->out);
		ft_putstr_fd(head->key, parc->out);
		ft_putstr_fd("=", parc->out);
		ft_putstr_fd("\"", parc->out);
		ft_putstr_fd(head->content, parc->out);
		ft_putstr_fd("\"", parc->out);
		ft_putstr_fd("\n", parc->out);
	}
	else if (index == 2 && head->flag == 0)
	{
		ft_putstr_fd("declare -x ", parc->out);
		ft_putstr_fd(head->key, parc->out);
		ft_putstr_fd("\n", parc->out);
	}
}

void	p_env(t_env *head, t_parc *parc)
{
	while (head != NULL)
	{
		if (head->content != NULL && ft_strcmp(head->key, "OLDPWD")
			&& ft_strcmp(head->key, "?") && head->flag == 0)
			print_env(parc, head, 0);
		head = head->next;
	}
}

void	env(t_env *head, char *str, t_parc *parc)
{
	t_env	*exp;
	t_env	*fexp;

	exp = NULL;
	if (ft_strcmp(str, "env") == 0)
		p_env(head, parc);
	else if (ft_strcmp(str, "export") == 0)
	{
		exp = sorted_env(head);
		fexp = exp;
		while (exp != NULL)
		{
			if (ft_strcmp(exp->key, "_") && ft_strcmp(exp->key, "?"))
			{
				if (exp->content != NULL && exp->flag == 0)
					print_env(parc, exp, 1);
				else if (exp->content == NULL && exp->flag == 0)
					print_env(parc, exp, 2);
			}
			exp = exp->next;
		}
		lst_clear_env(fexp);
	}
}
