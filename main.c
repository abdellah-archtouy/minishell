#include "mini.h"

struct	g_glo my = {0,0};

void	ft_readline(int sig)
{
	(void)sig;
	my.g_exit = 130;
	if (my.e_flag == 1)
	{
		close(STDIN_FILENO);
		my.e_flag = 0;
	}
	else if (my.e_flag == 1)
		return ;
	else if (my.e_flag == 0 && waitpid(-1, NULL, WNOHANG) != 0)
	{
		my.g_exit = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_history(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_joine_word(t_list *tmp)
{
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (ft_strchr(tmp->content, '\'') || ft_strchr(tmp->content, '\"'))
			{
				tmp->flag = 1;
				tmp->content = quotes_remover(tmp->content);
			}
		}
		tmp = tmp->next;
	}
}

int	ft_parcing(char *input, char ***str, t_parc	**parc, t_env **env)
{
	t_list	*head;
	char	**str1;

	head = NULL;
	(void)str;
	if (syntaxe_error(input))
		return (printf("syntax error\n"), 1);
	if (tokenizer(input, &str1, env))
		return (printf("syntax error\n"), 1);
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

// void	my()
// {
// 	system("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**str;
	t_parc	*parc;
	t_env	*envir;

	(void)av;
	(void)env;
	str = NULL;
	parc = NULL;
	if (ac != 1)
		return (1);
	my.e_flag = 0;
	// atexit(my);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_readline);
	rl_catch_signals = 0;
	envi(env, &envir);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("\033[11C\033[1Aexit\n");
			signal(SIGINT, SIG_IGN);
			exit(1);
		}
		if (ft_history(input))
		{
			add_history(input);
			if (ft_parcing(input, &str, &parc, &envir) == 0)
				builting_m_cmd(parc, envir, env);
			if (parc != NULL)
			{
				ft_lstclear_par(&parc);
				parc = NULL;
			}
		}
		free(input);
	}

	return (0);
}
