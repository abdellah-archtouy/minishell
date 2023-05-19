#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	{
		printf("Error: \"\n");
		exit(1);
	}
	if (b % 2 != 0)
	{
		printf("Error: \'\n");
		exit(1);
	}
}

void	ft_parcing(char *input)
{
	int	i;

	i = 0;
	printf("input = %s\n", input);
	ft_parc(input);
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|'
			|| input[i] == '$' || input[i] == '"' || input[i] == '\'')
			printf("input[%d] = %c\n", i, input[i]);
		i++;
	}
}

void	ft_readline(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)env;
	signal(SIGINT, &ft_readline);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		add_history(input);
		ft_parcing(input);
	}
}
