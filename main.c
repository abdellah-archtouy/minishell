#include "mini.h"

int	ft_getfile(char *input, int i)
{
	int	j = 0;
	char	*file = NULL;

	i++;
	while (input[i] == ' ')
		i++;
	while (input[i] != ' ')
	{
		file[j] = input[i];
		i++;
		j++;
	}
	file[j] = '\0';
	int fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error: open\n");
		exit(1);
	}
	return (fd);
}

void	ft_parc(char *input)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	a = 0;
	b = 0;
	while (input[i])
	{
		if (input[i] == '"')
			a++;
		if (input[i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0)
		printf("Error: \n");
	else if (b % 2 != 0)
		printf("Error: \n");
}

void	ft_parcing(char *input)
{
	int	i;

	i = 0;
	ft_parc(input);
	while (input[i])
	{
		i++;
	}
}

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
	int i;

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

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		in;
	int		out;

	(void)av;
	(void)env;
	in = 0;
	out = 1;
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
		ft_parcing(input);
		free(input);
	}
}
