NAME = main
NAMEB = checker

SRC = main.c

SRCB = 
 

OBJ = $(SRC:%.c=%.o)

OBJB = $(SRCB:%.c=%.o)


CFALGS =  -Wall -Wextra -Werror

CPPFLAGS="-I/goinfre/aarchtou/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/aarchtou/homebrew/opt/readline/lib" -lreadline

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