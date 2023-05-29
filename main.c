#include "mini.h"

void	ft_readline(int sig)
{
	if (sig == SIGINT)
	{
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

int	ft_parcing(char *input, char ***str, t_parc	**parc, t_env **env)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	if (syntaxe_error(input))
		return (1);
	if (tokenizer(input, str))
		return (1);
	lexer(*str, &head);
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

void	fun()
{
	system("leaks main");
}

int	main(int ac, char **av, char **env)
{
	atexit(fun);
	char	*input;
	char	**str;
	t_parc	*parc;
	t_env	*head;

	(void)av;
	(void)env;
	str = NULL;
	parc = NULL;
	if (ac != 1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_readline);
	rl_catch_signals = 0;
	envi(env, &head);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			// if (parc)
			// 	ft_lstclear_par(&parc);
			// free(input);
			exit(0);
		}
		if (ft_history(input))
		{
			add_history(input);
			if (ft_parcing(input, &str, &parc, &head) == 0 && parc)
			{
				printf("%s\n", parc->content[0]);
				// printf("%s\n", parc->content[1]);
				builting(parc, head);
			}
			else
				printf("syntax error\n");
			if (parc)
				ft_lstclear_par(&parc);
		}
		free(input);
	}
	return (0);
}