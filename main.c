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
	char	**str1;

	i = 0;
	head = NULL;
	(void)str;
	if (syntaxe_error(input))
		return (1);
	if (tokenizer(input, &str1))
		return (1);
	lexer(str1, &head);
	if (ft_parc(&head, parc, env))
		return (1);
	return (0);
}
	// t_list	*pop = head;
	// while (pop)
	// {
	// 	printf("str %s --- type %d\n", pop->content, pop->type);
	// 	pop = pop->next;
	// }
	// printf("=============================================\n");
	// int a = 0;
	// while ((*parc))
	// {
	// 	a = 0;
	// 	while ((*parc)->content[a])
	// 	{
	// 		printf("%s\n",(*parc)->content[a++]);
	// 	}
	// 		// printf("%d\n",(*parc)->out);
	// 		// printf("%d\n",(*parc)->in);
	// 	printf("==============\n");
	// 	(*parc) = (*parc)->next;
	// }

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
	atexit(my);
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
				builting(parc, envir);
			else
				printf("syntax error\n");
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
			// t_parc *ppp=parc;
			// while (ppp)
			// {
			// 	int i = 0;
			// 	while (ppp->content[i])
			// 	{
			// 		printf("%s\n", ppp->content[i]);
			// 		i++;
			// 	}
			// 	ppp = ppp->next;
			// }

			// while (head != NULL)
			// {
			// 	printf("%s=%s\n", head->key, head->content);
			// 	head = head->next;
			// }
