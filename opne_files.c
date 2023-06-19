/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opne_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchtou <aarchtou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:18:41 by tmiftah           #+#    #+#             */
/*   Updated: 2023/06/19 20:10:18 by aarchtou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

extern t_glo	g_my;

int	ft_get_fd_out(char *str, int t)
{
	int	fd;

	fd = 0;
	if (str[0] == '\0')
		return (write(2, "ambiguous redirect\n", 23), -1);
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

int	ft_open_doc(char *input, int *fd, t_list *ptr, t_env *env)
{
	int	i;

	i = 0;
	signal(SIGINT, ft_signal);
	input = readline(">");
	if (ptr->flag == 0 && input)
		input = ft_expand(input, env);
	if (isatty(STDIN_FILENO) == 0)
	{
		*fd = -1;
		g_my.quit = 1;
		dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
		return (1);
	}
	if (input == NULL || ft_strcmp(input, ptr->content) == 0)
	{
		free(input);
		return (1);
	}
	i = 0;
	while (input[i])
		write(*fd, &input[i++], 1);
	write(*fd, "\n", 1);
	free(input);
	return (0);
}

int	ft_get_fd_doc(t_list *ptr, t_env *env)
{
	int		fd;
	char	*input;
	char	*tmp;

	fd = 0;
	input = NULL;
	tmp = ft_get_doc();
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), fd);
	g_my.e_flag = 1;
	while (1)
	{
		if (ft_open_doc(input, &fd, ptr, env) == 1)
			break ;
	}
	close(fd);
	if (fd != -1)
		fd = open(tmp, O_RDONLY);
	free (tmp);
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
