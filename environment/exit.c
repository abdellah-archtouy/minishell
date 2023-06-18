/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:08:54 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 18:08:09 by tmiftah          ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
		i++;
	}
	return (1);
}

void	exit_t(char **str)
{
	int				r;
	int				i;
	unsigned char	exi;

	i = 1;
	if (str[i] && ft_int(str[i]) && str[i + 1] != NULL)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[i], 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else if (str[i] && ft_int(str[i]))
	{
		exi = ft_atoi(str[i]);
		r = (int)exi;
		exit(r);
	}
	else if (str[i] && ft_int(str[i]) == 0)
	{
		printf("minishell: %s: numeric argument required\n", str[i]);
		exit(0);
	}
	else
		exit(0);
}
