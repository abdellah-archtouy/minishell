NAME = minishell

SRC = main.c libf.c split.c utils.c lexer.c syntaxe_error.c export.c parcer.c libf2.c ft_strjoin.c ft_strdup.c ft_split1.c execution.c parsing_utils.c
 
OBJ = $(SRC:%.c=%.o)

CFALGS =  -Wall -Wextra -Werror #-fsanitize=address

USER := $(shell id -un)

CPPFLAGS="-I/goinfre/$(USER)/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/$(USER)/homebrew/opt/readline/lib" -lreadline

VAR= $(CPPFLAGS) $(LDFLAGS)

CC = cc 

INCLUDE = mini.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(VAR) $(OBJ) -o $(NAME)

%.o : %.c $(INCLUDE)
	$(CC) $(CFALGS) $(CPPFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) 

re: fclean all
