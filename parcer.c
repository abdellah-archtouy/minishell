/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:19:11 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 21:23:26 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_parc_helper(t_list **ptr, int *in, int *out)
{
	if ((*ptr)->type == RINPUT)
		*in = ft_ft_get_fd_in((*ptr)->next->content);
	else if ((*ptr)->type == ROUTPUT)
		*out = ft_get_fd_out((*ptr)->next->content, 1);
	else if ((*ptr)->type == APAND)
		*out = ft_get_fd_out((*ptr)->next->content, 2);
	else if ((*ptr)->type == HEREDOC)
		*in = ft_get_fd_doc((*ptr)->next->content);
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

int	ft_word_count(t_list *head)
{
	int	i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	return (i);
}

char	**ft_parc2(int *i, int *in, int *out, t_list **ptr)
{
	char	**str;

	*i = 0;
	*in = 0;
	*out = 1;
	str = malloc((ft_word_count((*ptr)) + 1) * 8);
	while ((*ptr) != NULL && (*ptr)->type != PIPE)
	{
		if ((*ptr)->type == WORD)
		{
			str[*i] = ft_strdup((*ptr)->content);
			(*i)++;
		}
		else
			ft_parc_helper(ptr, in, out);
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
	str[*i] = NULL;
	return (str);
}

int	ft_parc(t_list **ptr, t_parc **parc, t_env	**env)
{
	char	**str1;
	int		i;
	int		in;
	int		out;

	while ((*ptr) != NULL)
	{
		str1 = ft_parc2(&i, &in, &out, ptr);
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
