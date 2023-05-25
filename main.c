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

int	ft_parcing(char *input, char ***str)
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
	while (head)
	{
		if (head->type == PIPE)
			printf("str\t%s\tPIPE\n", head->content);
		else if (head->type == HEREDOC)
			printf("str\t%s\tHEREDOC\n", head->content);
		else if (head->type == RINPUT)
			printf("str\t%s\tRINPUT\n", head->content);
		else if (head->type == ROUTPUT)
			printf("str\t%s\tROUTPUT\n", head->content);
		else if (head->type == APAND)
			printf("str\t%s\tAPAND\n", head->content);
		else if (head->type == WORD)
			printf("str\t%s\tWORD\n", head->content);
		head = head->next;
	}
	printf("=============================================\n");
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
	int		in;
	t_exp	*head;
	int		out;
	// t_mini	mini;

	(void)av;
	(void)env;
	in = 0;
	out = 1;
	str = NULL;
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
		if (ft_parcing(input, &str) == 0)
		{
			envi(env, &head);
			while (head != NULL)
			{
				printf("%s=%s\n", head->key, head->content);
				head = head->next;
			}
			// execution
		}
		else ft_error("syntax error\n");
	}
}
