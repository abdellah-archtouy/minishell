/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:25:11 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/18 22:05:26 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_var(char *input, int *i, t_env	*env)
{
	char	*str;

	(*i)++;
	if (input[*i] == 0)
		return (ft_strdup("$"));
	if (ft_help_variabel(input, i, &str, *i))
		return (ft_strdup(""));
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			if (env->content)
				return (free(str), ft_strdup(env->content));
			if (!env->content)
				return (free(str), ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

void	dobel_norm(char	*input, int	*i, char **str, t_env *envp)
{
	char	*str1;

	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$' && input[*i + 1] != '\"' && input[*i + 1] != ' ')
		{
			str1 = ft_get_var(input, i, envp);
			*str = ft_strjoin(*str, str1);
		}
		else
		{
			str1 = ft_get_char(NULL, input[*i]);
			*str = ft_strjoin(*str, str1);
			(*i)++;
		}
		free(str1);
	}
}

char	*ft_get_dobel(char	*input, int *i, t_env	*envp)
{
	char	*str;
	char	*str1;

	str = ft_strdup("");
	str1 = ft_get_char(NULL, input[*i]);
	str = ft_strjoin(str, str1);
	(*i)++;
	free(str1);
	dobel_norm(input, i, &str, envp);
	str1 = ft_get_char(NULL, input[*i]);
	str = ft_strjoin(str, str1);
	free(str1);
	if (input[*i] != '\0')
		(*i)++;
	return (str);
}

void	ft_get_str(t_list *list, char **str)
{
	while (list)
	{
		*str = ft_strjoin(*str, list->content);
		free(list->content);
		free(list);
		list = list->next;
	}
	free(list);
}

char	*ft_expand(char *input, t_env *envp)
{
	int		i;
	t_list	*list;
	char	*str;

	i = 0;
	list = NULL;
	str = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
			ft_lstadd_back(&list, ft_lstnew(ft_get_var(input, &i, envp), 5));
		if (input[i] == '\'')
			ft_lstadd_back(&list, ft_lstnew(ft_get_qout(input, &i), 5));
		if (input[i] == '\"')
			ft_lstadd_back(&list, ft_lstnew(ft_get_dobel(input, &i, envp), 5));
		if (input[i] && input[i] != '\"' && input[i] != '\'' && input[i] != '$')
		{
			ft_lstadd_back(&list, ft_lstnew(ft_get_char(NULL, input[i]), 5));
			i++;
		}
	}
	ft_get_str(list, &str);
	return (free(input), str);
}
