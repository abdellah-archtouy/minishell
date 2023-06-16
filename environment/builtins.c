/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:20 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/15 20:55:21 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**env_empty(int *r)
{
	char	**str;

	str = malloc(6 * 8);
	str[0] = ft_strdup("PWD=/Users/tmiftah/Desktop/minishell");
	str[1] = ft_strdup("SHLVL=0");
	str[2] = ft_strdup("_=/usr/bin/env");
	str[3] = ft_strdup("OLDPWD");
	str[4] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	str[5] = NULL;
	(*r)++;
	return (str);
}

void	envi(char **env, t_env **head)
{
	int		i;
	int		r;
	char	*key;
	char	*content;

	i = 0;
	r = 0;
	key = NULL;
	content = NULL;
	if (env[0] == NULL)
		env = env_empty(&r);
	while ((env)[i])
	{
		key = get_chars((env)[i], 0);
		content = get_chars((env)[i], 1);
		if (ft_strcmp(key, "SHLVL") == 0)
			update_shell_level(&content, r);
		lstadd_back_env(head, ft_lstnew_env(key, content));
		i++;
	}
	if (r > 0)
		lstch_env(*head, "PATH")->flag = 1;
	lstadd_back_env(head, ft_lstnew_env(ft_strdup("?"), ft_strdup("0")));
}

int	fun(char *input, char c)
{
	int	i;

	i = 0;
	if (input[i] == '-' && input[i + 1] == 0)
		return (1);
	if (input[i] == '-')
		i++;
	while (input[i])
	{
		if (input[i] != c)
			return (1);
		i++;
	}
	return (0);
}

void	builtins(t_parc *parc, t_env **l_env)
{
	if (lstch_env(*l_env, "?")->content)
		free(lstch_env(*l_env, "?")->content);
	lstch_env(*l_env, "?")->content = ft_strdup("0");
	if (parc->content[0] == NULL || l_env == NULL)
		return ;
	if ((ft_strcmp(parc->content[0], "env") == 0
			|| ft_strcmp(parc->content[0], "export") == 0)
		&& parc->content[1] == NULL)
		env(*l_env, parc->content[0], parc);
	else if (ft_strcmp(parc->content[0], "export") == 0 && parc->content[1])
		add_var(l_env, parc->content);
	else if (ft_strcmp(parc->content[0], "unset") == 0)
		unset(l_env, parc->content);
	else if (ft_strcmp(parc->content[0], "echo") == 0 && parc->content[1])
		echo(parc);
	else if (ft_strcmp(parc->content[0], "cd") == 0)
		cd(parc->content, l_env);
	else if (ft_strcmp(parc->content[0], "pwd") == 0)
		pwd(parc->content, parc);
	else if (ft_strcmp(parc->content[0], "exit") == 0)
		return (printf("exit\n"), exit(0));
	else
		execute_cmd(parc, *l_env);
}

void	builtins1(t_parc *parc, t_env **l_env)
{
	if (lstch_env(*l_env, "?")->content)
		free(lstch_env(*l_env, "?")->content);
	lstch_env(*l_env, "?")->content = ft_strdup("0");
	if (parc->content[0] == NULL || l_env == NULL)
		return ;
	if ((ft_strcmp(parc->content[0], "env") == 0
			|| ft_strcmp(parc->content[0], "export") == 0)
		&& parc->content[1] == NULL)
		env(*l_env, parc->content[0], parc);
	else if (ft_strcmp(parc->content[0], "export") == 0 && parc->content[1])
		add_var(l_env, parc->content);
	else if (ft_strcmp(parc->content[0], "unset") == 0)
		unset(l_env, parc->content);
	else if (ft_strcmp(parc->content[0], "echo") == 0 && parc->content[1])
		echo(parc);
	else if (ft_strcmp(parc->content[0], "cd") == 0)
		cd(parc->content, l_env);
	else if (ft_strcmp(parc->content[0], "pwd") == 0)
		pwd(parc->content, parc);
	else if (ft_strcmp(parc->content[0], "exit") == 0)
		return (printf("exit\n"), exit(0));
	else
		execute_m_cmd(parc, *l_env);
	exit(1);
}
