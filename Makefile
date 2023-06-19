NAME = minishell

SRC =	environment/env.c \
		environment/env_utils.c \
		environment/export.c \
		environment/unset.c \
		environment/add_var.c \
		environment/exit.c \
		environment/builtins.c \
		environment/builtins_pwd.c \
		execution.c \
		parcer3.c \
		execution2.c \
		expand.c \
		ft_error.c \
		expand2.c \
		ft_split1.c \
		ft_strdup.c \
		ft_strjoin.c \
		lexer.c \
		libf.c \
		libf1.c \
		libf2.c \
		main.c \
		opne_files.c \
		parcer.c \
		parsing_utils.c \
		signals.c \
		split.c \
		ft_aitoia.c \
		syntaxe_error.c \
		utils.c 

OBJ = $(SRC:%.c=%.o)

CFALGS =  -Wall -Wextra -Werror

USER := $(shell id -un)

CPPFLAGS="-I/goinfre/$(USER)/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/$(USER)/homebrew/opt/readline/lib" -lreadline

VAR= $(CPPFLAGS) $(LDFLAGS) #-fsanitize=address -g

CC = cc 

INCLUDE = mini.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(VAR)  $(OBJ) -o $(NAME)

%.o : %.c $(INCLUDE)
	$(CC) $(CFALGS) $(CPPFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) 

re: fclean all
