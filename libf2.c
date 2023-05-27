
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
		return (free(str), ft_strdup(""));
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			str2 = ft_strdup(env->content);
			// puts(str2);
			return (free(str), str2);
		}
		env = env->next;
	}
	return (free(str), strdup(""));
}

char	*ft_check_variabel(char *content, t_env *env, int l, int a)
{
	int		i;
	char	**ptr;
	char	*str;

	i = 0;
	(void)l;
	str = malloc(1);
	ptr = ft_split1(content, '$');
	if (content[0] != '$')
	{
		free(str);
		str = ft_strdup(ptr[0]);
		i++;
	}
	while(a-- > 0)
	{
		while (ptr[i])
		{
			str = ft_strjoin(str, ft_replace_variyabel(ptr[i], env));
			i++;
		}
	}
	free(content);
	return (str);
}

int	ft_get_$(char *ptr)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (ptr[i])
	{
		if(ptr[i] == '$')
			b++;
		i++;
	}
	return (b);
}

t_parc	*ft_parcnew(char **content, int in, int out, t_env *env)
{
	t_parc	*a;
	int		i;
	char	**str;
	// char	*str1;

	i = 0;
	str = NULL;
	a = (void *)malloc(sizeof(t_parc));
	if (a == 0)
		return (0);
	while (content[i])
		rev_char(content[i++]);
	str = malloc(i);
	i = 0;
	while (content[i])
	{
		if (ft_get_$(content[i]) > 0)
			str[i] = ft_check_variabel(content[i], env, 0, ft_get_$(content[i]));
		else
		{
			str[i] = ft_strdup(content[i]);
		}
		i++;
	}
	a->content = str;
	i = 0;
	while (a->content[i])
	{
		printf("sss%s\n", a->content[i++]);
	}
	
	a->in = in;
	a->out = out;
	a->next = 0;
	return (a);
}
