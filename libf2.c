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

t_parc	*ft_parclast(t_parc *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_help_variabel(char *content, int *a, char **str, int i)
{
	if (content[*a] == '?')
		return (*str = ft_substr(content, i, 1), (*a)++, 0);
	else if ((content[*a] >= 'a' && content[*a] <= 'z')
		|| (content[*a] >= 'A' && content[*a] <= 'Z') || content[*a] == '_')
	{
		while (content[*a] && ((content[*a] >= 'a' && content[*a] <= 'z')
				|| (content[*a] >= 'A' && content[*a] <= 'Z')
				|| content[*a] == '_'
				|| (content[*a] >= '0' && content[*a] <= '9')))
		{
			(*a)++;
		}
		*str = ft_substr(content, i, *a - i);
	}
	else
		return ((*a)++, 1);
	return (0);
}

char	*ft_replace_variyabel(char *content, t_env *env)
{
	int		i;
	char	*str;
	char	*str2;
	int		l;

	l = -1;
	i = 0;
	str = NULL;
	if (ft_help_variabel(content, &i, &str, i))
		return (free(str), ft_substr(content, i, ft_strlen(content) - i));
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			str2 = ft_strjoin(ft_strdup(env->content),
					&content[ft_strlen(str)]);
			return (free(str), str2);
		}
		env = env->next;
	}
	return (free(str), ft_substr(content, i, ft_strlen(content) - i));
}

t_parc	*ft_parcnew(char **content, int in, int out, t_env *env)
{
	t_parc	*a;

	(void)env;
	a = (void *)malloc(sizeof(t_parc));
	if (a == 0)
		return (0);
	a->content = content;
	a->in = in;
	a->out = out;
	a->next = 0;
	return (a);
}
