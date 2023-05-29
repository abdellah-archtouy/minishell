
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
			str2 = ft_strjoin(ft_strdup(env->content), &content[ft_strlen(str)]);
			return (free(str), str2);
		}
		env = env->next;
	}
	return (free(str), ft_strdup(""));
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

char	*ft_check_variabel(char *content, t_env *env, int a)
{
	int		i;
	int		b;
	int		l;
	char	**ptr;
	char	*str;
	char	*str1;

	i = 0;
	b = 0;
	l = 0;
	str = ft_strdup("");
	while (content[i])
	{
		if(content[i] == '\'')
		{
			i++;
			if (i > 1)
            {
                free(str);
                str = ft_substr(content, 0, i - 1);
                if (ft_get_$(str) > 0)
               		str = ft_check_variabel(str, env, ft_get_$(str));
            }
			l = i -1;
			while(content[i] && content[i] != '\'')
				i++;
			b = i + 1;
		}
		i++;
	}
	if (b != 0)
	{
		// free(str);
		str1 =  ft_substr(content, l, b - l);
		str = ft_strjoin(str, str1);
		free(str1);
		ptr	= ft_split1(&content[b], '$');
	}
	else
	{
		ptr = ft_split1(content, '$');
		if (content[0] != '$')
		{
			free(str);
			str = ft_strdup(ptr[0]);
			i++;
		}
	}
	i = 0;
	while(a-- > 0)
	{
		while (ptr[i])
		{
			str1 = ft_replace_variyabel(ptr[i], env);
			str = ft_strjoin(str, str1);
			free(str1);
			i++;
		}
	}
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	free(content);
	return (str);
}

t_parc	*ft_parcnew(char **content, int in, int out, t_env *env)
{
	t_parc	*a;
	int		i;

	i = 0;
	a = (void *)malloc(sizeof(t_parc));
	if (a == 0)
		return (0);
	while (content[i])
		rev_char(content[i++]);
	i = 0;
	while (content[i])
	{
		if (ft_get_$(content[i]) > 0)
			content[i] = ft_check_variabel(content[i], env, ft_get_$(content[i]));
		i++;
	}
	i = 0;
	// while(content[i])
	// 	printf("%s\n", content[i++]);
	a->content = content;
	i = 0;
	a->in = in;
	a->out = out;
	a->next = 0;
	return (a);
}
