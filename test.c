#include "mini.h"

// char	*add_space(char *input)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	str = malloc(ft_strlen(input) * 2);
// 	while (input[i])
// 	{
// 		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
// 		{
// 			str[j++] = input[i++];
// 			if (input[i] && input[i - 1] == '\'')
// 				while (input[i] && input[i] != '\'')
// 					str[j++] = input[i++];
// 			if (input[i] && input[i - 1] == '\"')
// 				while (input[i] && input[i] != '\"')
// 					str[j++] = input[i++];
// 			str[j++] = input[i];
// 		}
// 		else if (input[i] && is_special(input[i]))
// 		{
// 			str[j++] = ' ';
// 			if (input[i] == input[i + 1])
// 				str[j++] = input[i++];
// 			str[j++] = input[i];
// 			str[j++] = ' ';
// 		}
// 		else
// 			str[j++] = input[i];
// 		i++;
// 	}
// 	str[j] = 0;
// 	free(input);
// 	return (str);
// }

int	ft_get_fd_out(char *str, int t)
{
	int fd;

	fd = 0;
	if (t == 1)
		fd = open(str, O_RDWR | O_CREAT, 0644);
	else if (t == 2)
		fd = open(str , O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
		return (perror("open"), fd);
	return (fd);
}

int main(int ac, char **av)
{
	char *str = "dsuvds";
	int i = 0;

	int fd = ft_get_fd_out("abdo", 1);

		printf("%d\n", fd);
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	

}