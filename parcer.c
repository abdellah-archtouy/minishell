
#include "mini.h"

int	ft_get_fd_out(char *str, int t)
{
	int fd;

	fd = 0;
	if (t == 1)
		fd = open(str , O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (t == 2)
		fd = open(str , O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	return (fd);
}

t_parc *ft_parc(t_list **ptr)
{
	t_parc *parc = NULL;
	char *str;
	int in;
	int out;

	while ((*ptr) != NULL)
	{
		in = 0;
		out = 1;
		str = ft_strdup("");
		while ((*ptr) != NULL /*&& (*ptr)->next != 0*/ &&  (*ptr)->type != PIPE)
		{
			if ((*ptr)->type == WORD)
			{
				str = ft_strjoin(str, (*ptr)->content);
				str = ft_strjoin(str, " ");
			}
			else if ((*ptr)->type == RINPUT)
			{
				// in = ft_ft_get_fd_in((*ptr)->next->content);
				(*ptr) = (*ptr)->next;
			}
			else if ((*ptr)->type == ROUTPUT)
			{
				out = ft_get_fd_out((*ptr)->next->content, 1);
				(*ptr) = (*ptr)->next;
			}
			else if ((*ptr)->type == APAND)
			{
				out = ft_get_fd_out((*ptr)->next->content, 2);
				(*ptr) = (*ptr)->next;
			}
			else if ((*ptr)->type == HEREDOC)
			{
				// out = ft_get_fd_doc((*ptr)->next->content);
				(*ptr) = (*ptr)->next;
			}
			(*ptr) = (*ptr)->next;
		}
		ft_parcadd_back(&parc, ft_parcnew(ft_split(str), in, out));
		if ((*ptr) != NULL)
			(*ptr) = (*ptr)->next;
	}
	int a = 0;
	while (parc)
	{
		a = 0;
		while(parc->content[a])
		{
			printf("%s\n",parc->content[a++]);
		}
		printf("==============\n");
		parc = parc->next;
	}
	return parc;
}
