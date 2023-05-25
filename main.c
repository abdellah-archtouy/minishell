#include "mini.h"

void	ft_readline(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
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
	return (0);
}
	// int a = 0;
	// while ((*parc))
	// {
	// 	a = 0;
	// 	printf("abd");
	// 	while((*parc)->content[a])
	// 	{
	// 		printf("%s\n",(*parc)->content[a++]);
	// 	}
	// 	printf("==============\n");
	// 	(*parc) = (*parc)->next;
	// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**str;
	t_parc	*parc;

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
			// execution
		}
		else
			printf("syntax error\n");
	}
	return (0);
}
