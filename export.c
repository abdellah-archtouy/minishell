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

void	lstadd_back_env(t_env **lst, t_env *new)
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
		lstadd_back_env(head, ft_lstnew_exp(key, content));
		i++;
	}

}

int	ft_lstsize_env(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

int	is_sorted(t_env *exp)
{
	while (exp->next != NULL)
	{
		if (ft_strcmp(exp->key , exp->next->key) > 0)
			return (0);
		exp = exp->next;
	}
	return (1);
}

t_env	*sorted_env(t_env *exp)
{
	t_env	*tmp = NULL;
	t_env	*save;
	char	*a;
	char	*b;

	while (exp != NULL)
	{
		a = ft_strdup(exp->key);
		b = ft_strdup(exp->content);
		lstadd_back_env(&tmp, ft_lstnew_exp(a, b));
		exp = exp->next;
	}
	save = tmp;
	while (is_sorted(tmp) == 0)
	{
		save = tmp;
		while (save->next != NULL)
		{
			if (ft_strcmp(save->key, save->next->key) > 0)
			{
				a = ft_strdup(save->key);
				b = ft_strdup(save->content);
				free(save->key);
				free(save->content);
				save->key = save->next->key;
				save->content = save->next->content;
				save->next->key = a;
				save->next->content = b;
			}
			save = save->next;
		}
	}
	return (tmp);
}

void	lst_clear_env(t_env **env)
{
	t_env	*head;

	while (*env != NULL)
	{
		head = (*env)->next;
		free((*env)->key);
		free((*env)->content);
		free(*env);
		*env = head;
		// env = env->next;
	}
}

void	env(t_env *head , char *str)
{
	t_env	*exp;

	exp = NULL;
	if (ft_strcmp(str, "env") == 0)
		while (head != NULL)
		{
			if (head->content[0] != 0)
				printf("%s=%s\n", head->key, head->content);
			head = head->next;
		}
	else if (ft_strcmp(str, "export") == 0)
	{
		exp = sorted_env(head);
		while (exp != NULL)
		{
			printf("declare -x %s=\"%s\"\n", exp->key, exp->content);
			exp = exp->next;
		}
		// lst_clear_env(&exp);
	}
}

// void	add_var(t_env *env, char *key, char *content)
// {

// }

void	builting(t_parc *parc, t_env *l_env)
{
	if (ft_strcmp(parc->content[0], "env") == 0
		|| (ft_strcmp(parc->content[0], "export") == 0 && parc->content[1] == NULL))
		env(l_env, parc->content[0]);
	// else if (ft_strcmp(parc->content[0], "export") == 0 && ft_strcmp(parc->content[1], "+"))
		// add_var()
	// lst_clear_env(&l_env);
}


