#include "mini.h"

t_env	*ft_lstnew_env(char *key, char *content)
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
		if (found != NULL)
		{
			size = found - string;
			returned = malloc(size + 1);
		}
		else
			return (ft_strdup(string));
		while(string[i] && string[i] != '=')
		{
			returned[i] = string[i];
			i++;
		}
		returned[i] = 0;
	}
	else if (index == 1 && found != NULL)
	{
		size = &string[ft_strlen(string) - 1] - found;
		j = ft_strlen(string) - size - 1;
		if (string[j] == '=')
			j++;
		returned = malloc(size + 1);
		while (string[j])
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
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
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
		lstadd_back_env(head, ft_lstnew_env(key, content));
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

t_env	*copy_list(t_env *env)
{
	char	*a;
	char	*b;
	t_env	*exp;

	exp = NULL;
	while (env != NULL)
	{
		a = env->key;
		b = env->content;
		lstadd_back_env(&exp, ft_lstnew_env(a, b));
		env = env->next;
	}
	return (exp);
}

t_env	*sorted_env(t_env *exp)
{
	char	*a;
	char	*b;
	t_env	*tmp;
	t_env	*save;

	tmp = copy_list(exp);
	save = tmp;
	while (is_sorted(save) == 0)
	{
		tmp = save;
		while (tmp->next != NULL)
		{
			if ((ft_strcmp(tmp->key, tmp->next->key) > 0))
			{
				a = tmp->key;
				b = tmp->content;
				tmp->key = tmp->next->key;
				tmp->content = tmp->next->content;
				tmp->next->key = a;
				tmp->next->content = b;
			}
			tmp = tmp->next;
		}
	}
	return (save);
}

void	lst_clear_env(t_env *env)
{
	t_env	*head;

	while (env != NULL)
	{
		head = env->next;
		free(env);
		env = head;
	}
	env = NULL;
}

void	env(t_env *head , char *str)
{
	t_env	*exp;
	t_env	*fexp;

	exp = NULL;
	if (ft_strcmp(str, "env") == 0)
		while (head != NULL)
		{
			if (head->content != NULL)
				printf("%s=%s\n", head->key, head->content);
			head = head->next;
		}
	else if (ft_strcmp(str, "export") == 0)
	{
		exp = sorted_env(head);
		fexp = exp;
		while (exp != NULL)
		{
			if (exp->content != NULL)
				printf("declare -x %s=\"%s\"\n", exp->key, exp->content);
			else if (exp->content == NULL)
				printf("declare -x %s\n", exp->key);
			exp = exp->next;
		}
		lst_clear_env(fexp);
	}
}

int	node_existences(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key/*, ft_strlen(env->key)*/) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}

int	equal_num(char *input)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		if (input[i] == '-')
			return (1);
		if (input[i] == '+')
			p++;
		i++;
	}
	if (p > 1)
		return (1);
	return (0);
}

int	parsing(char **input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		j = 0;
		if (equal_num(input[i]))
			return (1);
		while (input[i][j] && input[i][j] != '=')
		{
			if ((input[i][j] >= 'A' && input[i][j] <= 'Z')
			|| (input[i][j] >= 'a' && input[i][j] <= 'z')
				|| input[i][j] == '_' || input[i][j] == '+')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	add_var(t_env *env, char **str)
{
	int		i;
	char	*content;
	char	*key;
	t_env	*head;

	head = env;
	i = 1;
	if (parsing(str))
		return ;
	while (str[i])
	{
		key = get_chars(str[i], 0);
		content = get_chars(str[i], 1);
		if (node_existences(env, key) && ft_strchr(key, '+') == 0)
			lstadd_back_env(&env, ft_lstnew_env(key, content));
		else if (node_existences(env, key) == 0 || ft_strchr(key, '+'))
		{
			if (ft_strchr(key, '+') == 0)
			{
				while (head != NULL)
				{
					if (ft_strcmp(head->key, key) == 0)
						break;
					head = head->next;
				}
				free(key);
				free(head->content);
				head->content = content;
			}
			else if (ft_strchr(key, '+'))
			{
				while (head != NULL)
				{
					if (ft_strncmp(head->key, key, ft_strlen(head->key)) == 0)
						break;
					head = head->next;
				}
				free(key);
				head->content = ft_strjoin_ex(head->content, content);
				free(content);
			}
		}
		i++;
	}
}

void	unset(t_env *env, char **str)
{
	int		i;
	int		j;
	t_env	*head;
	t_env	*head0;

	i = 0;
	j = 0;
	head = env;
	head0 = env;
	while (str[i])
	{
		j = 0;
		while(str[i][j])
			if ((str[i][j] >= 'A' && str[i][j] <= 'Z')
			|| (str[i][j] >= 'a' && str[i][j] <= 'z')
				|| str[i][j] == '_')
				j++;
			else
				return ;
		i++;
	}
	i = 1;
	while (str[i])
	{
		head = env;
		head0 = env;
		while (head != NULL)
		{
			if (ft_strcmp(head->key, str[i]) == 0)
				break;
			head = head->next;
		}
		if (head == env)
		{
			env = env->next;
			free (head);
		}
		while (head0 != NULL && head != env)
		{
			if (head0->next == head)
			{
				head0->next = head->next;
				free(head);
				break ;
			}
			head0 = head0->next;
		}
		i++;
	}
}

void	builting(t_parc *parc, t_env *l_env)
{
	if ((ft_strcmp(parc->content[0], "env") == 0
		|| ft_strcmp(parc->content[0], "export") == 0) && parc->content[1] == NULL)
		env(l_env, parc->content[0]);
	else if (ft_strcmp(parc->content[0], "export") == 0 && parc->content[1])
		add_var(l_env, parc->content);
	else if (ft_strcmp(parc->content[0], "unset") == 0)
		unset(l_env, parc->content);
}
