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

void	d_s_q_remover(t_list **head)
{
	int		i;
	char	*str;
	t_list	*h;

	h = *head;
	str = NULL;
	while (h != NULL)
	{
		i = 0;
		if (h->content[i] != '\'' && h->content[i]
			!= '\"' && dollar_exist(h->content) == 1)
        {
            h = h->next;
            continue ;
        }
		while (h->content[i] && h->type == WORD)
		{
			if (h->content[i] == '\'')
			{
				str = single_quote(h->content);
				free(h->content);
				h->content = str;
				break;
			}
			else if (h->content[i] == '\"')
			{
				str = double_quote(h->content);
				free(h->content);
				h->content = str;
				break;
			}
			i++;
		}
		h = h->next;
	}
}


int strlen_q(char *input)
{
    int i = 0;
    int j = 0;
    while (input[i])
    {
        if(input[i] == '\'')
        {
            i++;
            while (input[i] != '\'')
            {
                i++;
                j++;
            }
            if (input[i] == '\'')
                i++;
            continue ;
        }
        else if(input[i] == '\"')
        {
            i++;
            while (input[i] != '\"')
            {
                i++;
                j++;
            }
            if (input[i] == '\"')
                i++;
            continue ;
        }
        j++;
        i++;
    }
    return (j);
}

char    *quotes_remover(char *input)
{
    int    i;
    int    j;
    char *str;

    i = 0;
    j = 0;
    str = malloc(strlen_q(input) + 1);
    while (input[i])
    {
        if (input[i] != '\"' && input[i] != '\'' && input[i])
            str[j++] = input[i++];
        if (input[i] == '\"' && input[i])
        {
            i++;
            while (input[i] != '\"' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\"')
                i++;
        }
        if (input[i] == '\'' && input[i])
        {
            i++;
            while (input[i] != '\'' && input[i])
                str[j++] = input[i++];
            if (input[i] == '\'')
                i++;
        }
    }
    str[j] = 0;
    return (str);
}

// void	d_s_q_remover(t_parc *parc)
// {
//     int		i;
//     int		j;
//     char	*str;

//     i = 0;
//     while (parc && parc->content[i])
//     {
//         j = 0;
//         if (parc->content[i][j] != '\'' && parc->content[i][j]
// 			!= '\"' && dollar_exist(parc->content[i]) == 1)
//         {
//             i++;
//             continue ;
//         }
//         while (parc->content[i][j])
//         {

//             if (parc->content[i][j] == '\'')
//             {
//                 str = single_quote(parc->content[i]);
//                 free(parc->content[i]);
//                 parc->content[i] = str;
//                 break;
//             }
//             else if (parc->content[i][j] == '\"')
//             {
//                 str = double_quote(parc->content[i]);
//                 free(parc->content[i]);
//                 parc->content[i] = str;
//                 break;
//             }
//             j++;
//         }
//         i++;
// 		parc = parc->next;
//     }
// }