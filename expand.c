#include "mini.h"


int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	ft_get_dolar(char *ptr)
{
	int	i;
	int	b;
	int	r;

	i = 0;
	r = 1;
	b = 0;
	while (ptr[i])
	{
		if (ptr[i] == '\'' || ptr[i] == '\"' || ptr[i] == '$')
			i++;
		else
		{
			r = 0;
			break ;
		}
	}
	if (r == 0)
		i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			b++;
		i++;
	}
	return (b);
}

int	test(char *str, int i)
{
	int	start;
	int	end;
	int	index;

	start = 0;
	end = 0;
	index = i;
	while (index >= 0)
	{
		if (str[index] == '\"')
		{
			start = -1;
			break ;
		}
		index--;
	}
	index = i;
	while (str[index])
	{
		if (str[index] == '\"')
		{
			end = -1;
			break ;
		}
		index++;
	}
	if (start == -1 && end == -1)
		return (1);
	return (0);
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
		if (content[i] == '\'')
		{
			if (test(content, i))
				break ;
			i++;
			if (i > 1)
			{
				free(str);
				str = ft_substr(content, 0, i - 1);
				if (ft_get_dolar(str) > 0)
					str = ft_check_variabel(str, env, ft_get_dolar(str));
			}
			l = i -1;
			while (content[i] && content[i] != '\'')
				i++;
			b = i + 1;
		}
		i++;
	}
	i = 0;
	if (b != 0)
	{
		str1 = ft_substr(content, l, b - l);
		str = ft_strjoin(str, str1);
		free(str1);
		ptr = ft_split1(&content[b], '$');
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
	while (a-- > 0)
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
