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

int	ft_parcing(char *input, char ***str, t_parc	**parc)
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
	t_list	*pop = head;
	while (pop)
	{
		printf("str %s --- type %d\n", pop->content, pop->type);
		pop = pop->next;
	}
	printf("=============================================\n");
	if (ft_parc(&head, parc))
		return (1);
	int a = 0;
	while ((*parc))
	{
		a = 0;
		while ((*parc)->content[a])
		{
			printf("%s\n",(*parc)->content[a++]);
			printf("%d\n",(*parc)->out);
			printf("%d\n",(*parc)->in);
		}
		printf("==============\n");
		(*parc) = (*parc)->next;
	}
	return (0);
}

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**str;
	t_parc	*parc;
	// t_exp	*head;

	(void)av;
	(void)env;
	str = NULL;
	parc = NULL;
	if (ac != 1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_readline);
	rl_catch_signals = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (ft_history(input))
			add_history(input);
		if (ft_parcing(input, &str, &parc) == 0)
		{
			// envi(env, &head);
			// while (head != NULL)
			// {
			// 	printf("%s=%s\n", head->key, head->content);
			// 	head = head->next;
			// }
			// execution
		}
		else printf("syntax error\n");
	}
	return (0);
}
