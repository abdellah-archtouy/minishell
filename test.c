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

// int	ft_get_fd_out(char *str, int t)
// {
// 	int fd;

// 	fd = 0;
// 	if (t == 1)
// 		fd = open(str, O_RDWR | O_CREAT, 0644);
// 	else if (t == 2)
// 		fd = open(str , O_CREAT | O_RDWR | O_APPEND);
// 	if (fd == -1)
// 		return (perror("open"), fd);
// 	return (fd);
// }

// int main(int ac, char **av)
// {
// 	char *str = "dsuvds";
// 	int i = 0;

// 	int fd = ft_get_fd_out("abdo", 1);

// 		printf("%d\n", fd);
// 	while (str[i])
// 	{
// 		write(fd, &str[i], 1);
// 		i++;
// 	}
	

// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** lines;
    int count;
    int capacity;
} Heredoc;

Heredoc* create_heredoc() {
    Heredoc* heredoc = (Heredoc*)malloc(sizeof(Heredoc));
    heredoc->lines = NULL;
    heredoc->count = 0;
    heredoc->capacity = 0;
    return heredoc;
}

void add_line(Heredoc* heredoc, const char* line) {
    if (heredoc->count >= heredoc->capacity) {
        int new_capacity = (heredoc->capacity == 0) ? 1 : (heredoc->capacity * 2);
        char** new_lines = (char**)realloc(heredoc->lines, new_capacity * sizeof(char*));
        if (new_lines == NULL) {
            // Error handling: Failed to allocate memory
            return;
        }
        heredoc->lines = new_lines;
        heredoc->capacity = new_capacity;
    }

    char* new_line = strdup(line);
    if (new_line == NULL) {
        // Error handling: Failed to allocate memory
        return;
    }

    heredoc->lines[heredoc->count] = new_line;
    heredoc->count++;
}

void free_heredoc(Heredoc* heredoc) {
    if (heredoc == NULL) {
        return;
    }

    for (int i = 0; i < heredoc->count; i++) {
        free(heredoc->lines[i]);
    }

    free(heredoc->lines);
    free(heredoc);
}

char* get_content(Heredoc* heredoc) {
    int total_length = 0;
    for (int i = 0; i < heredoc->count; i++) {
        total_length += strlen(heredoc->lines[i]) + 1;  // +1 for newline character
    }

    char* content = (char*)malloc(total_length + 1);  // +1 for null terminator
    if (content == NULL) {
        // Error handling: Failed to allocate memory
        return NULL;
    }

    char* current_position = content;
    for (int i = 0; i < heredoc->count; i++) {
        strcpy(current_position, heredoc->lines[i]);
        current_position += strlen(heredoc->lines[i]);
        *(current_position++) = '\n';
    }
    *current_position = '\0';

    return content;
}

// Example usage
int main() {
    Heredoc* heredoc = create_heredoc();
    add_line(heredoc, "This is line 1.");
    add_line(heredoc, "This is line 2.");

    char* content = get_content(heredoc);
    printf("%s\n", content);

    free(content);
    free_heredoc(heredoc);

    return 0;
}
