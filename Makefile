NAME = main
NAMEB = checker

SRC = main.c

SRCB = 
 

OBJ = $(SRC:%.c=%.o)

OBJB = $(SRCB:%.c=%.o)


CFALGS =  -Wall -Wextra -Werror

USER := $(shell id -un)

CPPFLAGS="-I/goinfre/$(USER)/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/$(USER)/homebrew/opt/readline/lib" -lreadline

VAR= $(CPPFLAGS) $(LDFLAGS)

CC = cc

INCLUDE =

all: $(NAME)

$(NAME): $(OBJ)

bonus : $(NAMEB)

$(NAMEB): $(OBJB)
	$(CC)  $(VAR) $(OBJB) -o $(NAMEB)

%.o : %.c $(INCLUDEB)
	$(CC)  $(CFALGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	@rm -rf $(NAME) $(NAMEB)

re: fclean all