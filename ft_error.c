/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:37 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 15:13:20 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_print_error(char *str)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, " ", 1);
	if (ft_strchr(str, '/') != 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	**ft_get_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (ft_split1(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

char	**ft_get_env(t_env	*env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc((ft_lstsize_env(env) + 1) * 8);
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(envp[i], env->content);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
