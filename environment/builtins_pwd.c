/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:55:14 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/15 20:56:59 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	echo_flag(char **content, int *r, int *i)
{
	int	j;

	j = 0;
	while (content[(*i)])
	{
		j = 0;
		if (content[(*i)][j] == '-')
		{
			if (fun(&content[(*i)][j], 'n'))
				break ;
			(*r)++;
		}
		else
			break ;
		(*i)++;
	}
}

void	echo(t_parc *parc)
{
	int		i;
	int		r;

	i = 1;
	r = 0;
	echo_flag(parc->content, &r, &i);
	while (parc->content[i])
	{
		ft_putstr_fd(parc->content[i++], parc->out);
		if (parc->content[i] != NULL)
			ft_putstr_fd(" ", parc->out);
	}
	if (r == 0)
		ft_putstr_fd("\n", parc->out);
}

void	cd(char **str, t_env **env)
{
	char	buff[1024];
	char	*tmp;

	getcwd(buff, 1024);
	tmp = str[1];
	if ((str[1] && ft_strcmp(str[1], "~") == 0) || str[1] == NULL)
		tmp = lstch_env(*env, "HOME")->content;
	if (chdir(tmp) == -1)
	{
		if (lstch_env(*env, "?")->content)
			free(lstch_env(*env, "?")->content);
		lstch_env(*env, "?")->content = ft_strdup("1");
		return ;
	}
	if (lstch_env(*env, "OLDPWD")->content)
		free(lstch_env(*env, "OLDPWD")->content);
	lstch_env(*env, "OLDPWD")->content = ft_strdup(buff);
	getcwd(buff, 1024);
	if (lstch_env(*env, "PWD")->content)
		free(lstch_env(*env, "PWD")->content);
	lstch_env(*env, "PWD")->content = ft_strdup(buff);
}

void	pwd(char **str, t_parc *parc)
{
	char	buff[1024];

	(void)str;
	if (getcwd(buff, 1024) != NULL)
	{
		ft_putstr_fd(buff, parc->out);
		ft_putstr_fd("\n", parc->out);
	}
}

t_env	*copy_list(t_env *env)
{
	t_env	*exp;

	exp = NULL;
	while (env != NULL)
	{
		lstadd_back_env(&exp, ft_lstnew_env(env->key, env->content));
		ft_lstlast_env(exp)->flag = env->flag;
		env = env->next;
	}
	return (exp);
}
