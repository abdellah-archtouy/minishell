
#include "mini.h"

char	**ft_get_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (ft_split1(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

void	execute_m_cmd(t_parc *parcer, t_env *env, char **tenv)
{
	char	**path1;
	char	*str;
	int		i;

	i = 0;
	path1 = ft_get_path(env);
	while (path1[i])
	{
		if (ft_strchr(parcer->content[0], '/') == 0)
			str = ft_strjoin_path(path1[i], parcer->content[0]);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		str = NULL;
		i++;
	}
	if (str == NULL)
		return (printf("commende not found : %s\n",
				parcer->content[0]), exit(127));
	else if (execve(str, parcer->content, tenv) < 0)
		perror("execve");
	exit(0);
}

void	ft_execute(t_parc *parcer, char	**tenv, char **path1, char *str)
{
	int	i;

	i = 0;
	while (path1[i])
	{
		if (ft_strchr(parcer->content[0], '/') == 0)
			str = ft_strjoin_path(path1[i], parcer->content[0]);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		str = NULL;
		i++;
	}
	if (str == NULL)
		return (printf("commende not found : %s\n",
				parcer->content[0]), exit(127));
	else if (execve(str, parcer->content, tenv) < 0)
		perror("execve");
	exit(0);
}

void	execute_cmd(t_parc *parcer, t_env *env, char	**tenv)
{
	pid_t	id;
	char	**path1;
	char	*str;
	int		i;

	i = 0;
	str = parcer->content[0];
	g_flag = 1;
	id = fork();
	if (id == 0)
	{
		if (parcer->out != 1)
			dup2(parcer->out, 1);
		if (parcer->in != 0)
			dup2(parcer->in, 0);
		path1 = ft_get_path(env);
		ft_execute(parcer, tenv, path1, str);
	}
	g_flag = 0;
	waitpid(id, &i, 0);
}

void	builting_m_cmd(t_parc *parc, t_env	*env, char	**tenv)
{
	int	fd[2];
	int	pid;

	while (parc && parc->next)
	{
		if (pipe(fd) == -1)
			return (printf("error here\n"), exit(1));
		pid = fork();
		g_flag = 1;
		if (pid == 0)
		{
			// cloce(fd[1]);
			dup2(fd[1], 1);
			builting1(parc, env, tenv);
		}
		g_flag = 0;
		parc = parc->next;
	}
	if (parc)
	{
		builting(parc, env, tenv);
	}
	while (wait(NULL) != -1);
}
