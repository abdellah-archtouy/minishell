
#include "mini.h"

void	ft_parcadd_back(t_parc **lst, t_parc *new)
{
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	ft_parclast(*lst)->next = new;
}

t_parc	*ft_parclast (t_parc *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_parc	*ft_parcnew(char **content, int in, int out)
{
	t_parc	*a;

	a = (void *)malloc(sizeof(t_parc));
	if (a == 0)
		return (0);
	int i = 0;
	while (content[i])
		rev_char(content[i++]);
	a->content = content;
	a->in = in;
    a->out = out;
	a->next = 0;
	return (a);
}