
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
	puts("aa");
	exit(0);
}

void	execute_cmd(t_parc *parcer, t_env *env, char	**tenv)
{
	pid_t	id;
	char	**path1;
	char	*str;
	int		i;
	int		status;

	i = 0;
	str = parcer->content[0];
	e_flag = 1;
	id = fork();
	if (id == 0)
	{
		g_flag = 2;
		if (parcer->out != 1)
			dup2(parcer->out, 1);
		if (parcer->in != 0)
			dup2(parcer->in, 0);
		path1 = ft_get_path(env);
		ft_execute(parcer, tenv, path1, str);
	}
	e_flag = 0;
	waitpid(id, &status, 0);
	printf("status = %d\n", WEXITSTATUS(status));
}

void	builting_m_cmd(t_parc *parc, t_env	*env, char	**tenv)
{
	int	fd[2];
	int	pid;
	int	old;

	fd[0] = -1;
	fd[1] = -1;
	if (!parc->next)
	{
		builting(parc, env, tenv);
	}
	else
	{
		while (parc)
		{
			old = fd[0];
			if (pipe(fd) == -1)
				return (printf("error here\n"), exit(1));
			pid = fork();
			e_flag = 1;
			if (pid == 0)
			{
				close(fd[0]);
				if (old != -1)
					dup2(old, 0);
				if (parc->next)
					dup2(fd[1], 1);
				close(fd[1]);
				if (parc->in > 2)
					dup2(parc->in, 0);
				if (parc->out > 2)
					dup2(parc->out, 1);
				builting1(parc, env, tenv);
				exit(0);
			}
			e_flag = 0;
			parc = parc->next;
			close(fd[1]);
			close(old);
		}
		close(fd[0]);
		waitpid(pid, NULL, 0);
		while (wait(NULL) != -1)
			;
	}
}
