
#include "mini.h"

void	lexer(char	**str, t_list	**ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], RINPUT));
		else if (ft_strcmp(str[i], ">") == 0 )
			ft_lstadd_back(ptr, ft_lstnew(str[i], ROUTPUT));
		else if (ft_strcmp(str[i], ">>") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], APAND));
		else if (ft_strcmp(str[i], "<<") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], HEREDOC));
		else if (ft_strcmp(str[i], "|") == 0)
			ft_lstadd_back(ptr, ft_lstnew(str[i], PIPE));
		else
			ft_lstadd_back(ptr, ft_lstnew(str[i], WORD));
		i++;
	}
}

int	tokenizer(char *input, char ***str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)str;
	input = add_space(input);
	if (syntaxe_quotes(input))
		return (1);
	while (input[i])
	{
		if (input[i] != '\"' && input[i + 1] == '\"')
		{
			input[i + 1] = input[i];
			input[i] = '\"';
		}
		i++;
	}
	printf("%s\n", input);
	// rev_char(input);
	// *str = ft_split(input);
	// free(input);
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
