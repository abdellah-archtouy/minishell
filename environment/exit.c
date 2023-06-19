/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:08:54 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 13:54:33 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	exit_stat_update(t_env **env, int i)
{
	if (lstch_env(*env, "?")->content)
		free(lstch_env(*env, "?")->content);
	lstch_env(*env, "?")->content = ft_itoa(i);
}

int	ft_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	exit_norm(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	exit_t(char **str, t_env **env)
{
	int				i;
	long long		r;
	unsigned char	exi;

	i = 1;
	if (str[i] && ft_int(str[i]) && str[i + 1] != NULL)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[i], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		exit_stat_update(env, 1);
	}
	else if (str[i] && ft_int(str[i]))
	{
		exi = ft_atoi(str[i]);
		r = (int)exi;
		exit(r);
	}
	else if (str[i] && ft_int(str[i]) == 0)
	{
		exit_norm(str[i]);
		exit(255);
	}
	else
		exit(0);
}
