
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
	if ((content[*a] >= 'a' && content[*a] <= 'z')
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
		*str = ft_strjoin(*str, "=");
	}
	else
		return ((*a)++, 1);
	return (0);
}

char	*ft_replace_variyabel(char *content, int *a, char **env)
{
	int		i;
	char	*str;
	char	*str2;
	int		l;

	l = -1;
	i = 0;
	str = NULL;
	if (content[*a] == '$')
	{
		(*a)++;
		i = *a;
		if (ft_help_variabel(content, a, &str, i))
			return (free(str), ft_strdup(""));
		while (env[++l])
		{
			if (ft_strncmp(env[l], str, ft_strlen(str)) == 0)
			{
				str2 = ft_substr(env[l], ft_strlen(str),
						ft_strlen(env[l]) - ft_strlen(str));
				return (free(str), str2);

			}
		}
	}
	return (free(str), strdup(""));
}

char	**ft_check_variabel(char **content, char **env, int l, int a)
{
	char	*str;
	char	*str2;
	char	**str4;
	int		i;

	str4 = malloc(l);
	i = -1;
	while (++i < l)
	{
		a = -1;
		while (content[i][++a])
		{
			if (content[i][a] == '$')
			{
				str = ft_substr(content[i], 0, a);
				str2 = ft_replace_variyabel(content[i], &a, env);
				str = ft_strjoin(str, str2);
				free(str2);
				str2 = ft_substr(content[i], a, ft_strlen(content[i]) - a);
				str4[i] = ft_strjoin(str, str2);
				free(str2);
			}
			else
				str4[i] = content[i];
		}
		free(content[i]);
	}
	str4[l] = NULL;
	free(content);
	return (str4);
}

t_parc	*ft_parcnew(char **content, int in, int out, char **env)
{
	t_parc	*a;
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	a = (void *)malloc(sizeof(t_parc));
	if (a == 0)
		return (0);
	while (content[i])
		rev_char(content[i++]);
	a->content = ft_check_variabel(content, env, i, 0);
	a->in = in;
	a->out = out;
	a->next = 0;
	return (a);
}
