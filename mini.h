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
# define VARIA 6

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}				t_list;

typedef struct s_parc
{
	char			**content;
	int				in;
	int				out;
	struct s_list	*next;
}				t_parc;

typedef struct s_mini
{
	
}				t_mini;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
char	**ft_split(char const *s);
t_list	*ft_lstnew(char *content, int type);
int		ft_strcmp(const char *a, const char *b);
void	lexer(char	**str, t_list	**ptr);
t_parc	*ft_parcnew(char **content, int in, int out);
t_parc	*ft_parclast (t_parc *lst);
void	ft_parcadd_back(t_parc **lst, t_parc *new);
int		ft_strlen(char *str);
char	*add_space(char *input);
int		syntaxe_quotes(char *input);
void	rev_char(char *input);
int		tokenizer(char *input, char ***str);
int		is_special(char c);
t_parc	*ft_parc(t_list *ptr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		syntaxe_error(char *input);

#endif
