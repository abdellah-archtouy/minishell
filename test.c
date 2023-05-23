#include "mini.h"

char	*add_space(char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(input) * 2);
	while (input[i])
	{
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			str[j++] = input[i++];
			if (input[i] && input[i - 1] == '\'')
				while (input[i] && input[i] != '\'')
					str[j++] = input[i++];
			if (input[i] && input[i - 1] == '\"')
				while (input[i] && input[i] != '\"')
					str[j++] = input[i++];
			str[j++] = input[i];
		}
		else if (input[i] && is_special(input[i]))
		{
			str[j++] = ' ';
			if (input[i] == input[i + 1])
				str[j++] = input[i++];
			str[j++] = input[i];
			str[j++] = ' ';
		}
		else
			str[j++] = input[i];
		i++;
	}
	str[j] = 0;
	free(input);
	return (str);
}

int main(int ac, char **av)
{

}