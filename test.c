#include "mini.h"

// // char	*add_space(char *input)
// // {
// // 	int		i;
// // 	int		j;
// // 	char	*str;

// // 	i = 0;
// // 	j = 0;
// // 	str = malloc(ft_strlen(input) * 2);
// // 	while (input[i])
// // 	{
// // 		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
// // 		{
// // 			str[j++] = input[i++];
// // 			if (input[i] && input[i - 1] == '\'')
// // 				while (input[i] && input[i] != '\'')
// // 					str[j++] = input[i++];
// // 			if (input[i] && input[i - 1] == '\"')
// // 				while (input[i] && input[i] != '\"')
// // 					str[j++] = input[i++];
// // 			str[j++] = input[i];
// // 		}
// // 		else if (input[i] && is_special(input[i]))
// // 		{
// // 			str[j++] = ' ';
// // 			if (input[i] == input[i + 1])
// // 				str[j++] = input[i++];
// // 			str[j++] = input[i];
// // 			str[j++] = ' ';
// // 		}
// // 		else
// // 			str[j++] = input[i];
// // 		i++;
// // 	}
// // 	str[j] = 0;
// // 	free(input);
// // 	return (str);
// // }

// // int	ft_get_fd_out(char *str, int t)
// // {
// // 	int fd;

// // 	fd = 0;
// // 	if (t == 1)
// // 		fd = open(str, O_RDWR | O_CREAT, 0644);
// // 	else if (t == 2)
// // 		fd = open(str , O_CREAT | O_RDWR | O_APPEND);
// // 	if (fd == -1)
// // 		return (perror("open"), fd);
// // 	return (fd);
// // }

// // int main(int ac, char **av)
// // {
// // 	char *str = "dsuvds";
// // 	int i = 0;

// // 	int fd = ft_get_fd_out("abdo", 1);

// // 		printf("%d\n", fd);
// // 	while (str[i])
// // 	{
// // 		write(fd, &str[i], 1);
// // 		i++;
// // 	}
	

// // }

// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>

// // typedef struct {
// //     char** lines;
// //     int count;
// //     int capacity;
// // } Heredoc;

// // Heredoc* create_heredoc() {
// //     Heredoc* heredoc = (Heredoc*)malloc(sizeof(Heredoc));
// //     heredoc->lines = NULL;
// //     heredoc->count = 0;
// //     heredoc->capacity = 0;
// //     return heredoc;
// // }

// // void add_line(Heredoc* heredoc, const char* line) {
// //     if (heredoc->count >= heredoc->capacity) {
// //         int new_capacity = (heredoc->capacity == 0) ? 1 : (heredoc->capacity * 2);
// //         char** new_lines = (char**)realloc(heredoc->lines, new_capacity * sizeof(char*));
// //         if (new_lines == NULL) {
// //             // Error handling: Failed to allocate memory
// //             return;
// //         }
// //         heredoc->lines = new_lines;
// //         heredoc->capacity = new_capacity;
// //     }

// //     char* new_line = strdup(line);
// //     if (new_line == NULL) {
// //         // Error handling: Failed to allocate memory
// //         return;
// //     }

// //     heredoc->lines[heredoc->count] = new_line;
// //     heredoc->count++;
// // }

// // void free_heredoc(Heredoc* heredoc) {
// //     if (heredoc == NULL) {
// //         return;
// //     }

// //     for (int i = 0; i < heredoc->count; i++) {
// //         free(heredoc->lines[i]);
// //     }

// //     free(heredoc->lines);
// //     free(heredoc);
// // }

// // char* get_content(Heredoc* heredoc) {
// //     int total_length = 0;
// //     for (int i = 0; i < heredoc->count; i++) {
// //         total_length += strlen(heredoc->lines[i]) + 1;  // +1 for newline character
// //     }

// //     char* content = (char*)malloc(total_length + 1);  // +1 for null terminator
// //     if (content == NULL) {
// //         // Error handling: Failed to allocate memory
// //         return NULL;
// //     }

// //     char* current_position = content;
// //     for (int i = 0; i < heredoc->count; i++) {
// //         strcpy(current_position, heredoc->lines[i]);
// //         current_position += strlen(heredoc->lines[i]);
// //         *(current_position++) = '\n';
// //     }
// //     *current_position = '\0';

// //     return content;
// // }

// // // Example usage
// // int main() {
// //     Heredoc* heredoc = create_heredoc();
// //     add_line(heredoc, "This is line 1.");
// //     add_line(heredoc, "This is line 2.");

// //     char* content = get_content(heredoc);
// //     printf("%s\n", content);

// //     free(content);
// //     free_heredoc(heredoc);

// //     return 0;
// // }

//  #include <string.h>

// // int	ft_strlen(char *str)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (str[i])
// // 		i++;
// // 	return (i);
// // }

// // char	*ft_substr(char *s, unsigned int start, size_t len)
// // {
// // 	char	*ptr;
// // 	char	*tmp;
// // 	int		index;

// // 	tmp = (char *)s;
// // 	if (s == NULL)
// // 		return (NULL);
// // 	if (ft_strlen(s) < start)
// // 		len = 0;
// // 	else if (ft_strlen(s) < len)
// // 		len = ft_strlen(s);
// // 	index = 0;
// // 	ptr = (char *)malloc(sizeof(char) * (len + 1));
// // 	if (ptr == NULL)
// // 		return (NULL);
// // 	while (len && tmp[start])
// // 	{
// // 		ptr[index++] = tmp[start++];
// // 		len--;
// // 	}
// // 	ptr[index] = '\0';
// // 	return (ptr);
// // }

// int	ft_help_variabel(char *content, int *a, char **str, int i)
// {
// 	if ((content[*a] >= 'a' && content[*a] <= 'z')
// 		|| (content[*a] >= 'A' && content[*a] <= 'Z') || content[*a] == '_')
// 	{
// 		while (content[*a] && ((content[*a] >= 'a' && content[*a] <= 'z')
// 				|| (content[*a] >= 'A' && content[*a] <= 'Z')
// 				|| content[*a] == '_'
// 				|| (content[*a] >= '0' && content[*a] <= '9')))
// 		{
// 			(*a)++;
// 		}
// 		*str = ft_substr(content, i, *a - i);
// 		*str = ft_strjoin(*str, "=");
// 	}
// 	else
// 		return ((*a)++, 1);
// 	return (0);
// }

// char	*ft_replace_variyabel(char *content, int *a, char **env)
// {
// 	int		i;
// 	char	*str;
// 	char	*str2;
// 	int		l;

// 	l = -1;
// 	i = 0;
// 	if (content[*a] == '$')
// 	{
// 		(*a)++;
// 		i = *a;
// 		if (ft_help_variabel(content, a, &str, i))
// 			return (free(str), ft_strdup(""));
// 		while (env[++l])
// 		{
// 			if (ft_strncmp(env[l], str, ft_strlen(str)) == 0)
// 			{
// 				str2 = ft_substr(env[l], ft_strlen(str),
// 						ft_strlen(env[l]) - ft_strlen(str));
// 				return (free(str), str2);
// 			}
// 		}
// 	}
// 	return (free(str), strdup(""));
// }

// char	**ft_check_variabel(char **content, char **env, int i, int a)
// {
// 	char	*str;
// 	char	*str2;

// 	i = 0;
// 	// while (content[++i] != NULL)
// 	// {
// 		a = -1;
// 		while (content[i][++a])
// 		{
// 			if (content[i][a] == '$')
// 			{
// 				str = ft_substr(content[i], 0, a);
// 				str2 = ft_replace_variyabel(content[i], &a, env);
// 				str = ft_strjoin(str, str2);
// 				free(str2);
// 				str2 = ft_substr(content[i], a, ft_strlen(content[i]) - a);
// 				str = ft_strjoin(str, str2);
// 				free(str2);
// 			}
// 		}
// 		content[i] = str;
// 		free(str);
// 		printf("%s\n", content[i]);
// 	// }
// 	return (content);
// }
// void	my()
// {
// 	system("leaks a.out");
// }


#include <stdlib.h>
#include <string.h>

int	main()
{
	char *str = NULL;

	free(str);
	// atexit(my);
	// ft_check_variabel(&str, env,0 , 0);
}