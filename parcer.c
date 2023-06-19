/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:19:11 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 18:14:25 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_parc_helper(t_list **ptr, int *in, int *out, t_env *env)
{
	if ((*ptr)->type == RINPUT)
		*in = ft_ft_get_fd_in((*ptr)->next->content);
	else if ((*ptr)->type == ROUTPUT)
		*out = ft_get_fd_out((*ptr)->next->content, 1);
	else if ((*ptr)->type == APAND)
		*out = ft_get_fd_out((*ptr)->next->content, 2);
	else if ((*ptr)->type == HEREDOC)
		*in = ft_get_fd_doc((*ptr)->next, env);
	else
		return (0);
	free((*ptr)->content);
	free((*ptr));
	(*ptr) = (*ptr)->next;
	return (0);
}

void	rev_char1(char *input, int r)
{
	int	i;

	i = 0;
	if (r == 0)
	{
		while (input[i])
		{
			if (input[i] < 0)
				input[i] *= -1;
			i++;
		}
	}
	if (r == 1)
		while (input[i])
			input[i++] *= -1;
}

void	ft_word_count_helper(char *input, int *a, int *i)
{
	*a = 0;
	(*i)++;
	while (input[(*a)])
	{
		if (input[(*a)] == ' ' || input[(*a)] == '\t')
		{
			while (input[(*a)] && (input[(*a)] == ' ' || input[(*a)] == '\t'))
				(*a)++;
			if (input[(*a)] != '\0')
				(*i)++;
		}
		(*a)++;
	}
}

char	**ft_parc2(int *in, t_env *env, int *out, t_list **ptr)
{
	char	**str;
	char	**str1;
	int		i;
	int		a;

	i = 0;
	a = 0;
	*in = 0;
	*out = 1;
	str = malloc((ft_word_count((*ptr)) + 1) * 8);
	while ((*ptr) != NULL && (*ptr)->type != PIPE)
	{
		if ((*ptr)->type == WORD)
			ft_parc_norm2(ptr, &i, &str, &str1);
		else
			ft_parc_helper(ptr, in, out, env);
		if (*in < 0 || *out < 0)
			ft_parc_norm1(ptr, 0);
		else
			ft_parc_norm1(ptr, 1);
	}
	str[i] = NULL;
	return (str);
}

int	ft_parc(t_list **ptr, t_parc **parc, t_env	**env)
{
	char	**str1;
	int		in;
	int		out;

	while ((*ptr) != NULL)
	{
		str1 = ft_parc2(&in, *env, &out, ptr);
		ft_parcadd_back(parc, ft_parcnew(str1, in, out, *env));
		if ((*ptr) != NULL)
		{
			free((*ptr)->content);
			free((*ptr));
			(*ptr) = (*ptr)->next;
		}
	}
	return (0);
}
