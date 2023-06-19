/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:19:30 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 15:10:30 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*ft_get_char(char *str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	(void)str;
	str1 = malloc(2);
	if (!str1)
		return (NULL);
	str1[i++] = c;
	str1[i] = '\0';
	return (str1);
}

void	print_env_error(char *str, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	if (i == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

void	unset_norm(char *str, t_env **env)
{
	print_env_error(str, 1);
	exit_stat_update(env, 1);
}

void	add_var_norm(char *content, char *key)
{
	if (content)
		free(content);
	if (key)
		free(key);
}
