#include "mini.h"

extern	t_glo	g_my;

void	ft_dup(t_parc *parc, int *fd, int *old)
{

	close(fd[0]);
	if (parc->out > 2)
		dup2(parc->out, 1);
	else if (parc->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (parc->in > 2)
		dup2(parc->in, 0);
	else if (*old != -1)
	{
		dup2(*old, 0);
		close(*old);
	}
	if (parc->content[0] == NULL)
		exit(0);
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

	while (parc)
	{
		old = fd[0];
		if (pipe(fd) == -1)
			return (write(2, "PIPE\n", 5), exit(1));
		pid = fork();
		g_my.e_flag = 1;
		if (pid == 0)
			ft_exec2(env, parc, fd, old);
		g_my.e_flag = 0;
		ft_close(parc, fd, old);
		parc = parc->next;
	}
	waitpid(pid, &status, 0);
	while (wait(&status) != -1)
		;
	ft_check_exit(*env, status);
}

void	builting_m_cmd(t_parc *parc, t_env	**env)
{
	int		fd[2];
	t_parc	*par;

	fd[0] = -1;
	fd[1] = -1;
	par = parc;
	while (par)
	{
		if (par->in < 0 || par->out < 0)
		{
			g_my.g_exit = 1;
			ft_exite_status(*env);
			g_my.g_exit = 0;
			return ;
		}
		par = par->next;
	}
	if (!parc->next)
		builting(parc, env);
	else
		ft_exec1(parc, env, fd);
}
