#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "mini.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_help_variabel(char *content, int *a, char **str, int i)
{
	if (content[*a] == '?')
		return (*str = ft_substr(content, i, 1), 0);
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

int	ft_strncmp( char *a, char *b, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)a;
	s2 = (unsigned char *)b;
	if (!a || !b)
		return (-1);
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
		i++;
	if ((s1[i] - s2[i]) == 0)
		return (0);
	else if ((s1[i] - s2[i]) > 0)
		return (1);
	else
		return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		a;
	int		i;
	int		l;
	int		t;
	char	*ptr;

	i = 0;
	t = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	a = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(sizeof(char) * a);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[l++] = s1[i++];
	}
	while (s2[t])
	{
		ptr[l++] = s2[t++];
	}
	ptr[l] = '\0';
	// free(s1);
	return (ptr);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*ptr;
	char	*tmp;
	int		index;

	tmp = (char *)s;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s) < len)
		len = ft_strlen(s);
	index = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (len && tmp[start])
	{
		ptr[index++] = tmp[start++];
		len--;
	}
	ptr[index] = '\0';
	return (ptr);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0)
	{
	d[i] = s[i];
		i++;
		n--;
	}
	return (d);
}

char	*ft_strdup(char *s1)
{
	char	*s2;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == NULL)
		return (0);
	ft_memcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

char	*ft_get_qout(char *input, int *i, char	*str)
{
	int	a;

	a = *i;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	str = ft_strjoin(str, ft_substr(input, a+1, (*i - a) - 1));
	(*i)++;
	return (str);
}

int ft_str_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*ft_expand2(char *input, int *i, char	*str, char **envp)
{
	char	*str1;
	int		a;
	int		l;

	a = 0;
	l = *i;
	if (input[*i] == '$')
	{
		(*i)++;
		if (ft_help_variabel(input, i, &str1, *i) == 1)
			return (free(str), ft_strjoin(str,
					ft_substr(input, l, ft_strlen(input) - l)));
		while (envp[a])
		{
			if (ft_strncmp(envp[a], str1, ft_str_len(envp[a])) == 0)
			{
				str = ft_strjoin(str, ft_strdup(&envp[a][ft_strlen(str1) + 1]));
				return (str);
			}
			a++;
		}
	}
	return (free(str1), /*ft_strjoin(str, ft_substr(input,
				*i, ft_strlen(input) - *i))*/str);
}

char	*ft_get_char(char *str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	str1 = malloc(ft_strlen(str) + 2);
	while (str[i])
	{
		str1[i] = str[i];
		i++;
	}
	str1[i++] = c;
	str1[i] = '\0';
	free(str);
	return (str1);
}

char	*ft_expand_dobel(char *input, int *i, char *str, char **envp)
{
	int	a;

	a = (*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')
			str = ft_expand2(input, i, str, envp);
		if (input[*i] != '\"')
			str = ft_get_char(str, input[*i]);
		(*i)++;
	}
	return (str);
}


void	ft_expand(char *input, char **envp)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'')
			str = ft_get_qout(input, &i, str);
		else if (input[i] == '$')
			str = ft_expand2(input, &i, str, envp);
		else if (input[i] == '\"')
			str = ft_expand_dobel(input, &i, str, envp);
		else
		{
			str = ft_get_char(str, input[i]);
			i++;
		}
	}
	printf("%s\n", str);
}


int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	ft_expand("$\'USER\'", envp);
	// printf("%s\n", av[1]);
	// ft_expand(av[1], envp);
}
