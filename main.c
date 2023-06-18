/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:08:14 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/17 20:58:05 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_glo	g_my;

int	ft_parcing(char *input, char ***str, t_parc	**parc, t_env **env)
{
	t_list	*head;
	char	**str1;

	head = NULL;
	(void)str;
	if (syntaxe_error(input))
		return (printf("syntax error\n"), exit_stat_update(env, 1), 1);
	if (tokenizer(input, &str1, env))
		return (printf("syntax error\n"), exit_stat_update(env, 1), 1);
	lexer(str1, &head);
	ft_joine_word(head);
	if (ft_parc(&head, parc, env))
		return (1);
	return (0);
}

void	ft_lstclear_par(t_parc **lst)
{
	t_parc	*h;
	int		i;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		h = (*lst)->next;
		i = 0;
		while ((*lst)->content[i])
			free((*lst)->content[i++]);
		free((*lst)->content);
		free((*lst));
		*lst = h;
	}
	*lst = NULL;
}

void	ft_readline(char **str, t_env **envir, t_parc **parc)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("\033[11C\033[1Aexit\n");
			exit(0);
		}
		ft_exite_status(*envir);
		if (ft_history(input))
		{
			add_history(input);
			if (ft_parcing(input, &str, parc, envir) == 0)
				builtins_m_cmd(*parc, envir);
			if (parc != NULL)
			{
				ft_lstclear_par(parc);
				*parc = NULL;
			}
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	**str;
	t_parc	*parc;
	t_env	*envir;

	(void)av;
	str = NULL;
	parc = NULL;
	if (ac != 1)
		return (1);
	g_my.e_flag = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal);
	rl_catch_signals = 0;
	envi(env, &envir);
	ft_readline(str, &envir, &parc);
	return (0);
}
