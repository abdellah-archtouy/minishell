#include "mini.h"

extern	t_glo	g_my;

void	ft_dup(t_parc *parc, int *fd, int *old)
{
	close(fd[0]);
	if (parc->out > 2)
	{
		dup2(parc->out, 1);
		close(parc->out);
	}
	else if (parc->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (parc->in > 2)
	{
		dup2(parc->in, 0);
		close(parc->in);
	}
	else if (*old != -1)
	{
		dup2(*old, 0);
		close(*old);
	}
}

void	ft_exec2(t_env **env, t_parc *parc, int *fd, int old)
{
	signal(SIGQUIT, SIG_DFL);
	ft_dup(parc, fd, &old);
	builting1(parc, env);
}

void	ft_close(t_parc *parc, int *fd, int old)
{
	if (parc->in > 2)
		close(parc->in);
	if (parc->out > 2)
		close(parc->out);
	close(fd[1]);
	close(old);
	if (parc->next)
		close(fd[1]);
}

void	ft_exec1(t_parc *parc, t_env **env, int *fd)
{
	int	status;
	int	old;
	int	pid;
	int	id;

	while (parc)
	{
		old = fd[0];
		if (pipe(fd) == -1)
			return (printf("error here\n"), exit(1));
		pid = fork();
		g_my.e_flag = 1;
		if (pid == 0)
			ft_exec2(env, parc, fd, old);
		g_my.e_flag = 0;
		ft_close(parc, fd, old);
		parc = parc->next;
	}
	while (wait(&status) != -1)
	{
		if (id == pid)
			break ;
		id = wait(&status);
	}
	ft_check_exit(*env, status);
}

void	builting_m_cmd(t_parc *parc, t_env	**env)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (!parc->next)
		builting(parc, env);
	else
		ft_exec1(parc, env, fd);
}
