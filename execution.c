#include "mini.h"

extern	t_glo	g_my;

int	ft_execute_m_cmd(int *i, char **str, t_parc	*parcer, char **path1)
{
	if (ft_strchr(parcer->content[0], '/') == 0)
			*str = ft_strjoin_path(path1[*i], parcer->content[0]);
	if (access(*str, F_OK) == 0)
		return (1);
	free(*str);
	*str = NULL;
	(*i)++;
	return (0);
}

void	execute_m_cmd(t_parc *parcer, t_env *env)
{
	char	**path1;
	char	*str;
	int		i;
	char	**envp;

	i = 0;
	path1 = ft_get_path(env);
	if (!path1 && ft_strchr(parcer->content[0], '/') == 0)
		ft_print_error(parcer->content[0]);
	while (path1 && path1[i])
	{
		if (ft_execute_m_cmd(&i, &str, parcer, path1) == 1)
			break ;
	}
	if (ft_strchr(parcer->content[0], '/') != 0)
		str = ft_strdup(parcer->content[0]);
	if (str == NULL)
		return (ft_print_error(parcer->content[0]), exit(127));
	envp = ft_get_env(env);
	if (execve(str, parcer->content, envp) < 0)
		perror("execve");
	exit(1);
}

void	ft_execute(t_parc *parcer, t_env *env, char **path1, char *str)
{
	int		i;
	char	**envp;

	i = 0;
	while (path1 && path1[i])
	{
		if (ft_strchr(parcer->content[0], '/') == 0)
			str = ft_strjoin_path(path1[i], parcer->content[0]);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		str = NULL;
		i++;
	}
	if (!path1 && ft_strchr(parcer->content[0], '/') != 0)
		str = ft_strdup(parcer->content[0]);
	if (str == NULL)
		return (ft_print_error(parcer->content[0]), exit(127));
	envp = ft_get_env(env);
	if (execve(str, parcer->content, envp) < 0)
		perror("execve");
	exit(1);
}

void	execute_cmd(t_parc *parcer, t_env *env)
{
	pid_t	id;
	char	**path1;
	char	*str;
	int		i;
	int		status;

	i = 0;
	if (!parcer->content)
		exit(0);
	str = parcer->content[0];
	g_my.e_flag = 1;
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (parcer->out != 1)
			dup2(parcer->out, 1);
		if (parcer->in != 0)
			dup2(parcer->in, 0);
		path1 = ft_get_path(env);
		if (!path1 && ft_strchr(parcer->content[0], '/') == 0)
			ft_print_error(parcer->content[0]);
		ft_execute(parcer, env, path1, str);
	}
	g_my.e_flag = 0;
	waitpid(id, &status, 0);
	ft_check_exit(env, status);
}
