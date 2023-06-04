#include "mini.h"

t_globa glob;

void	ft_readline(int sig)
{
	(void)sig;
	if (g_flag == 1)
	{
		close(STDIN_FILENO);
		g_flag = 0;
	}
	else if (waitpid(-1, NULL, WNOHANG) != 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
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

int	ft_parcing(char *input, char ***str, t_parc	**parc, t_env **env)
{
	int		i;
	t_list	*head;
	char	**str1;

	i = 0;
	head = NULL;
	(void)str;
	if (syntaxe_error(input))
		return (printf("syntax error\n"), 1);
	if (tokenizer(input, &str1, env))
		return (printf("syntax error\n"), 1);
	lexer(str1, &head);
	if (ft_parc(&head, parc, env))
		return (1);
	return (0);
}


void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

void	ft_lstclear_par(t_parc **lst)
{
	t_parc	*h;
	int		i;

	i = 0;
	if (!lst)
		return ;
	while (*lst != NULL)
	{
		h = (*lst)->next;
		while ((*lst)->content[i])
			free((*lst)->content[i++]);
		free((*lst)->content);
		free((*lst));
		*lst = h;
	}
	*lst = NULL;
}

void	my()
{
	system("leaks main");
}

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
		exit(1);
	g_flag = 0;
	// atexit(my);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_readline);
	rl_catch_signals = 0;
	envi(env, &envir);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (ft_history(input))
		{
			add_history(input);
			if (ft_parcing(input, &str, &parc, &envir) == 0)
			{
				if (parc->next == NULL)
					builting(parc, envir);
				// else
				// 	builting_m_cmd(parc, envir);
			}
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
