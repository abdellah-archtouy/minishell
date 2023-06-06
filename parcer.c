#include "mini.h"

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

void	ft_close(int i)
{
	(void)i;
	close(i);
}

char	*ft_get_doc(void)
{
	char	*str;
	char	tmp[1];
	int		i;

	i = 0;
	str = ft_strdup("/tmp/her_doc");
	while (1)
	{
		if (access(str, F_OK) != 0)
			break ;
		else
		{
			tmp[0] = 'a' + i;
			str = ft_strjoin(str, tmp);
		}
		i++;
	}
	return (str);
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

	fd = 0;
	input = NULL;
	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), fd);
	g_flag = 1;
	while (1)
	{
		if (ft_open_doc(input, fd, content) == 1)
			break ;
	}
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	g_flag = 0;
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

int	ft_parc_helper(t_list **ptr, int *in, int *out)
{
	if ((*ptr)->type == RINPUT)
	{
		*in = ft_ft_get_fd_in((*ptr)->next->content);
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == ROUTPUT)
	{
		*out = ft_get_fd_out((*ptr)->next->content, 1);
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == APAND)
	{
		*out = ft_get_fd_out((*ptr)->next->content, 2);
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == HEREDOC)
	{
		*in = ft_get_fd_doc((*ptr)->next->content);
		free((*ptr)->content);
		free((*ptr));
		(*ptr) = (*ptr)->next;
	}
	if (*in == -1 || *out == -1)
		return (1);
	return (0);
}

void	rev_char1(char *input, int r)
{
	int	i;

	i = 0;
	if (r == 0)
		while (input[i])
		{
			if (input[i] < 0)
				input[i] *= -1;
			i++;
		}
	if (r == 1)
		while (input[i])
			input[i++] *= -1;
}

int	ft_parc(t_list **ptr, t_parc **parc, t_env	**env)
{
	char	*str;
	char	**str1;
	int		i;
	int		in;
	int		out;

	i = 0;
	while ((*ptr) != NULL)
	{
		in = 0;
		out = 1;
		str = ft_strdup("");
		while ((*ptr) != NULL && (*ptr)->type != PIPE)
		{
			if ((*ptr)->type == WORD)
			{
				rev_char1((*ptr)->content, 1);
				str = ft_strjoin(str, (*ptr)->content);
				str = ft_strjoin(str, " ");
			}
			else if (ft_parc_helper(ptr, &in, &out))
				return (free((*ptr)->content), free((*ptr)), free(str), -1);
			free((*ptr)->content);
			free((*ptr));
			(*ptr) = (*ptr)->next;
		}
		str1 = ft_split(str);
		while (str1[i])
			rev_char1(str1[i++], 0);
		ft_parcadd_back(parc, ft_parcnew(str1, in, out, *env));
		free(str);
		if ((*ptr) != NULL)
			(*ptr) = (*ptr)->next;
	}
	return (0);
}
