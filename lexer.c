#include "mini.h"

void	lexer(char	**str, t_list	**ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), RINPUT));
		else if (ft_strcmp(str[i], ">") == 0)
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), ROUTPUT));
		else if (ft_strcmp(str[i], ">>") == 0)
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), APAND));
		else if (ft_strcmp(str[i], "<<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), HEREDOC));
		else if (ft_strcmp(str[i], "|") == 0)
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), PIPE));
		else
			ft_lstadd_back(ptr, ft_lstnew(ft_strdup(str[i]), WORD));
		free(str[i]);
		i++;
	}
	free(str);
}

int	tokenizer(char *input, char ***str, t_env **env)
{
	int		i;
	char	**content;

	i = 0;
	input = add_space(input);
	if (syntaxe_quotes(input))
		return (free(input), 1);
	rev_char(input);
	*str = ft_split(input);
	content = *str;
	while (content[i])
		rev_char(content[i++]);
	i = 0;
	while (content[i])
	{
		if (ft_get_dolar(content[i]) > 0 &&
			ft_strncmp(content[i - 1], "<<", 2) != 0)
			content[i] = ft_check_variabel(content[i],
					*env, ft_get_dolar(content[i]));
		i++;
	}
	free(input);
	return (0);
}

int	syntaxe_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' && input[i])
		{
			i++;
			while (input[i] != '\"' && input[i])
				i++;
			if (input[i] == '\0')
				return (1);
		}
		else if (input[i] == '\'' && input[i])
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
			if (input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	rev_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' && input[i])
		{
			i++;
			while (input[i] != '\"' && input[i])
			{
				input[i] *= -1;
				i++;
			}
		}
		else if (input[i] == '\'' && input[i])
		{
			i++;
			while (input[i] != '\'' && input[i])
			{
				input[i] *= -1;
				i++;
			}
		}
		i++;
	}
}
