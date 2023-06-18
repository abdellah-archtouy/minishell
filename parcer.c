#include "mini.h"

int	ft_parc_helper(t_list **ptr, int *in, int *out)
{
	if ((*ptr)->type == RINPUT)
		*in = ft_ft_get_fd_in((*ptr)->next->content);
	else if ((*ptr)->type == ROUTPUT)
		*out = ft_get_fd_out((*ptr)->next->content, 1);
	else if ((*ptr)->type == APAND)
		*out = ft_get_fd_out((*ptr)->next->content, 2);
	else if ((*ptr)->type == HEREDOC)
		*in = ft_get_fd_doc((*ptr)->next->content);
	else
		return (0);
	free((*ptr)->content);
	free((*ptr));
	(*ptr) = (*ptr)->next;
	return (0);
}

void	rev_char1(char *input, int r)
{
	int	i;

	i = 0;
	if (r == 0)
	{
		while (input[i])
		{
			if (input[i] < 0)
				input[i] *= -1;
			i++;
		}
	}
	if (r == 1)
		while (input[i])
			input[i++] *= -1;
}

char	*ft_parc2(int *i, int *in, int *out, t_list **ptr)
{
	char	*str;

	*i = 0;
	*in = 0;
	*out = 1;
	str = ft_strdup("");
	while ((*ptr) != NULL && (*ptr)->type != PIPE)
	{
		if ((*ptr)->type == WORD)
		{
			if ((*ptr)->flag == 1)
				rev_char1((*ptr)->content, 1);
			str = ft_strjoin(str, (*ptr)->content);
			str = ft_strjoin(str, " ");
		}
		else
			ft_parc_helper(ptr, in, out);
		if (*in < 0 || *out < 0)
		{
			while ((*ptr) && (*ptr)->type != PIPE)
			{
				free((*ptr)->content);
				free((*ptr));
				(*ptr) = (*ptr)->next;
			}
		}
		else
		{
			free((*ptr)->content);
			free((*ptr));
			(*ptr) = (*ptr)->next;
		}
	}
	return (str);
}

int	ft_parc(t_list **ptr, t_parc **parc, t_env	**env)
{
	char	*str;
	char	**str1;
	int		i;
	int		in;
	int		out;

	while ((*ptr) != NULL)
	{
		str = ft_parc2(&i, &in, &out, ptr);
		str1 = ft_split(str);
		while (str1[i])
			rev_char1(str1[i++], 0);
		ft_parcadd_back(parc, ft_parcnew(str1, in, out, *env));
		free(str);
		if ((*ptr) != NULL)
		{
			free((*ptr)->content);
			free((*ptr));
			(*ptr) = (*ptr)->next;
		}
	}
	return (0);
}
