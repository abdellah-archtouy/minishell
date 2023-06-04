#include "mini.h"

int	dollar_exist(char *input)
{
	int i;

	i = 0;
	while (input[i])
		if (input[i++] == '$')
			return (1);
	return (0);
}

char	*single_quote(char *input)
{
	int r;
	int i;

	r = 0;
	i = 0;
	char *str;
	str = malloc(ft_strlen(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] != '\'')
		{
			str[r] = input[i];
			r++;
		}
		i++;
	}
	str[r] = 0;
	return (str);
}

char	*double_quote(char *input)
{
	int r;
	int i;

	r = 0;
	i = 0;
	char *str;
	str = malloc(ft_strlen(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] != '\"')
		{
			str[r] = input[i];
			r++;
		}
		i++;
	}
	str[r] = 0;
	return (str);
}

// void	d_s_q_remover(t_parc *parc)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	str = NULL;
// 	while (parc->content[i] != NULL)
// 	{
// 		j = 0;
// 		while (parc->content[i][j])
// 		{
// 			if (parc->content[i][j] == '\'' || parc->content[i][j] == '\"')
// 			{
// 				if (parc->content[i][j] == '\''/* && ft_get_$(parc->content) == 0*/)
// 				{
// 					str = single_quote(parc->content[i]);
// 					free(parc->content[i]);
// 					parc->content[i] = str;
// 				}
// 				else if (parc->content[i][j] == '\"'/* && ft_get_$(parc->content) == 0*/)
// 				{
// 					str = double_quote(parc->content[i]);
// 					free(parc->content[i]);
// 					parc->content[i] = str;
// 				}
// 				break;
// 			}
// 			j++;
// 		}
// 		i++;
// 		parc = parc->next;
// 	}
// }

void	d_s_q_remover(t_parc *parc)
{
    int		i;
    int		j;
    char	*str;

    i = 0;
    while (parc->content[i])
    {
        j = 0;
        if (parc->content[i][j] != '\'' && parc->content[i][j]
			!= '\"' && dollar_exist(parc->content[i]) == 1)
        {
            i++;
            continue ;
        }
        while (parc->content[i][j])
        {

            if (parc->content[i][j] == '\'')
            {
                str = single_quote(parc->content[i]);
                free(parc->content[i]);
                parc->content[i] = str;
                break;
            }
            else if (parc->content[i][j] == '\"')
            {
                str = double_quote(parc->content[i]);
                free(parc->content[i]);
                parc->content[i] = str;
                break;
            }
            j++;
        }
        i++;
    }
}