#include "mini.h"

extern t_glo	g_my;

int	ft_get_fd_out(char *str, int t)
{
	int	fd;

	fd = 0;
	if (t == 1)
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (t == 2)
		fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), fd);
	return (fd);
}

char	*ft_get_doc(void)
{
	static char	*str;
	static int	i;
	char		*tmp;

	while (1)
	{
		str = ft_itoa(i);
		tmp = ft_strjoin(ft_strdup("/tmp/"), str);
		free(str);
		if (access(tmp, F_OK) != 0)
			break ;
		free(tmp);
		i++;
	}
	return (tmp);
}

int	ft_open_doc(char *input, int fd, char *content)
{
	int	i;

	i = 0;
	signal(SIGINT, ft_readline);
	input = readline(">");
	if (isatty(STDIN_FILENO) == 0)
		dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
	if (input == NULL || ft_strcmp(input, content) == 0)
	{
		free(input);
		return (1);
	}
	i = 0;
	while (input[i])
		write(fd, &input[i++], 1);
	write(fd, "\n", 1);
	free(input);
	return (0);
}

int	ft_get_fd_doc(char *content)
{
	int		fd;
	char	*input;
	char	*tmp;

	fd = 0;
	input = NULL;
	tmp = ft_get_doc();
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free (tmp);
	if (fd == -1)
		return (perror("open"), fd);
	g_my.e_flag = 1;
	while (1)
	{
		if (ft_open_doc(input, fd, content) == 1)
			break ;
	}
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	g_my.e_flag = 0;
	return (fd);
}

int	ft_ft_get_fd_in(char *content)
{
	int	fd;

	fd = open(content, O_RDONLY, 0644);
	if (fd == -1)
		return (perror(content), fd);
	return (fd);
}
