#include "mini.h"

extern t_glo	g_my;

void	ft_readline(int sig)
{
	if (sig == 2 && g_my.e_flag == 1)
	{
		close(STDIN_FILENO);
		g_my.e_flag = 0;
	}
	else if (sig == 2 && g_my.e_flag == 1)
		return ;
	else if (sig == 2 && g_my.e_flag == 0 && waitpid(-1, NULL, WNOHANG) != 0)
	{
		g_my.g_exit = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_history(char *str)
{
	int	i;

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

void	ft_joine_word(t_list *tmp)
{
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (ft_strchr(tmp->content, '\'') || ft_strchr(tmp->content, '\"'))
			{
				tmp->flag = 1;
				tmp->content = quotes_remover(tmp->content);
			}
		}
		tmp = tmp->next;
	}
}

void	ft_exite_status(t_env *envir)
{
	t_env	*tmp;

	tmp = envir;
	if (g_my.g_exit)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "?") == 0)
			{
				free(tmp->content);
				tmp->content = ft_itoa(1);
			}
			tmp = tmp->next;
		}
		g_my.g_exit = 0;
	}
}