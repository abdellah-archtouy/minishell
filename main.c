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

int	syntaxe_quotes(char *input)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (*input)
	{
		if (*input == 34 || *input == 39)
		{
			if (*input == 34)
				a++;
			if (*input == 39)
				b++;
		}
		input++;
	}
	if (a % 2 != 0 || b % 2 != 0 )
	{
		printf("Error: \n");
		return (1);
	}
	return (0);
}

void	rev_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			while (input[i] && (input[i] == '\'' || input[i] == '"'))
				i++;
			while (input[i] && (input[i] != '\'' && input[i] != '"'))
				input[i++] *= -1;
		}
		i++;
	}
}

int	ft_check_helper1(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>'
			|| (input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				i++;
			}
			if (input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_helper(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (input[i] == '|')
				return (1);
		}
		else if (input[i] == '<')
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (input[i] == '>')
				return (1);
		}
		else if (input[i] == '>')
		{
			i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}
int	check_syntaxe(char	*input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '<')
	{
		if (input[i + 1] != '<')
			return (1);
	}
	else if (input[i] == '>')
		return (1);
	else if (input[i] == '|')
		return (1);
	if (ft_check_helper(input, i))
		return (1);
	if (ft_check_helper1(input))
		return (1);
	return (0);
}

int	tokenizer(char *input, char ***str)
{
	int	i;
	char **str1;

	i = 0;
	if (check_syntaxe(input))
		return(printf("syntx dsgd\n"), 1);
	if (syntaxe_quotes(input))
		return (1);
	rev_char(input);
	*str = ft_split(input);
	str1 = *str;
	while (str1[i])
		rev_char(str1[i++]);

	// if (rev_char(input))
	// 	return (1);
	return (0);
}

int	ft_parcing(char *input, char ***str)
{
	int	i;

	i = 0;
	if (tokenizer(input, str))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**str = NULL;
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
		if (ft_parcing(input, &str) == 0)
		{
			// execution
			// printf("%s\n", str[0]);
			// printf("%s\n", str[1]);
			// printf("%s\n", str[2]);
		}
		free(input);
	}
}
