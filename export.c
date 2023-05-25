#include "mini.h"
#include <string.h>

t_env	*ft_lstnew_exp(char *key, char *content)
{
	t_env	*a;

	a = (void *)malloc(sizeof(t_env));
	if (!a)
		return (0);
	a->content = content;
	a->key = key;
	a->next = NULL;
	return (a);
}

char	*ft_strchr(char *s, int c)
{
	char	*c1;

	c1 = (char *)s;
	while (*c1 != '\0')
	{
		if (*c1 == (char)c)
			return (c1);
		c1++;
	}
	if (*c1 == '\0' && *c1 == (char)c)
		return (c1);
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	int		ssize;
	int		r;
	char	*c1;

	ssize = ft_strlen(s);
	c1 = (char *)s;
	r = 0;
	while (ssize >= 0)
	{
		if (c1[ssize] == (char)c)
			return (c1 + ssize);
		else
			ssize--;
	}
	return (0);
}

char* get_chars(char* string, int index)
{
	char	*found;
	char	*returned = NULL;
	int		size;
	int		i;
	int		j;

	i = 0;
	found = ft_strchr(string, '=');
	if (index == 0)
	{
		size = found - string;
		returned = malloc(size + 1);
		while(string[i] && string[i] != '=')
		{
			returned[i] = string[i];
			i++;
		}
		returned[i] = 0;
	}
	else if (index == 1)
	{
		size = &string[ft_strlen(string) - 1] - found;
		j = ft_strlen(string) - size;
		if (string[j] == '=')
			j++;
		returned = malloc(size + 1);
		while(string[j])
		{
			returned[i] = string[j];
			i++;
			j++;
		}
		returned[i] = 0;
	}
	return (returned);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_exp(t_env **lst, t_env *new)
{
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	ft_lstlast_env(*lst)->next = new;
}

void	envi(char **env, t_env **head)
{
	int		i;
	char	*key = NULL;
	char	*content = NULL;

	i = 0;
	while (env[i])
	{
		key = get_chars(env[i], 0);
		content = get_chars(env[i], 1);
		lstadd_back_exp(head, ft_lstnew_exp(key, content));
		i++;
	}

}

void	env(t_env *head)
{
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->content);
		head = head->next;
	}
}

void	builting(t_parc *parc, t_env *l_env)
{
	if (ft_strcmp(parc->content[0], "env") == 0 || ft_strcmp(parc->content[0], "export") == 0)
		env(l_env);
	// else if (ft_strcmp(parc->content[0], "export") == 0)

}

void	export(t_env **envi, t_parc	*parc)
{
	int		i = 0;
	// t_parc	*h = parc;
	char	*str = ft_strdup("");
	while (parc->content[1])
	{
		if (str)
			free(str);
		str = ft_strjoin(str, parc->content[i]);
		i++;
	}
	var_parse(str);
}

