NAME = main
NAMEB = checker

SRC = main.c libf.c split.c utils.c lexer.c syntaxe_error.c ft_strdup.c ft_strjoin.c libf2.c parcer.c export.c

OBJ = $(SRC:%.c=%.o)

CFALGS =  -Wall -Wextra -Werror

USER := $(shell id -un)

CPPFLAGS="-I/goinfre/$(USER)/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/$(USER)/homebrew/opt/readline/lib" -lreadline

VAR= $(CPPFLAGS) $(LDFLAGS)

CC = cc

INCLUDE = mini.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC)  $(VAR) $(OBJ) -o $(NAME)

%.o : %.c $(INCLUDE)
	$(CC)  $(CFALGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	rm -rf $(NAME) $(NAMEB)

re: fclean all