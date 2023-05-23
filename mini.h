#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 0
# define RINPUT 1
# define ROUTPUT 2
# define APAND 3
# define HEREDOC 4
# define WORD 5

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}				t_list;

typedef struct s_lex
{
	char			*content;
	int				type;
	struct s_list	*next;
}				t_lex;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
char	**ft_split(char const *s);
int		check_syntaxe(char	*input);
t_list	*ft_lstnew(char *content, int type);
int		ft_strcmp(const char *a, const char *b);
void	lexer(char	**str, t_list	**ptr);
int		ft_strlen(char *str);
char	*add_space(char *input);
int		syntaxe_quotes(char *input);
void	rev_char(char *input);
int		tokenizer(char *input, char ***str);
int		is_special(char c);
int		syntaxe_error(char *input);

#endif
