#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 0
# define RINPUT 1
# define ROUTPUT 2
# define APAND 3
# define HEREDOC 4
# define WORD 5
# define VARIA 6

int	e_flag;

typedef struct g_glo
{
	int	e_flag;
	int	g_exit;
}		t_glo;

typedef struct s_list
{
	char			*content;
	int				type;
	int				flag;
	struct s_list	*next;
}				t_list;

typedef struct s_env
{
	char			*key;
	char			*content;
	int				flag;
	struct s_env	*next;
}				t_env;

typedef struct s_parc
{
	char			**content;
	int				in;
	int				out;
	struct s_parc	*next;
}				t_parc;

void	ft_exite_status(t_env *envir);
void	ft_print_error(char *str);
char	**ft_get_env(t_env	*env);
char	**ft_get_path(t_env *env);
int		ft_history(char *str);
void	ft_check_exit(t_env *env, int status);
void	ft_joine_word(t_list *tmp);
char	*ft_get_char(char *str, char c);
char	*ft_expand(char *input, t_env *envp);
t_parc	*ft_parcnew(char **content, int in, int out, t_env *env);
t_parc	*ft_parclast(t_parc *lst);
void	ft_parcadd_back(t_parc **lst, t_parc *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
char	**ft_split(char const *s);
char	**ft_split1(char const *s, char c);
t_list	*ft_lstnew(char *content, int type);
int		ft_strcmp(const char *a, const char *b);
void	lexer(char	**str, t_list	**ptr);
size_t	ft_strlen(char *str);
int		ft_help_variabel(char *content, int *a, char **str, int i);
char	*ft_replace_variyabel(char *content, t_env *env);
char	*add_space(char *input);
int		syntaxe_quotes(char *input);
char	*ft_strjoin_path(char *s1, char *s2);
void	rev_char(char *input);
int		ft_get_fd_out(char *str, int t);
int		ft_open_doc(char *input, int fd, char *content);
int		ft_ft_get_fd_in(char *content);
int		ft_get_fd_doc(char *content);
int		is_special(char c);
int		ft_parc(t_list **ptr, t_parc **parc, t_env **env);
int		ft_parcing(char *input, char ***str, t_parc	**parc, t_env **env);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		syntaxe_error(char *input);
int		ft_strncmp( char *a, char *b, size_t n);
char	*ft_substr(char *s, size_t start, size_t len);
void	export(t_env **envi, t_parc	*parc);
int		ft_get_dolar(char *ptr);
char	*ft_check_variabel(char *content, t_env *env, int a);
void	builting(t_parc *parc, t_env **l_env);
int		tokenizer(char *input, char ***str, t_env **env);
char	*ft_strjoin_wspace(char *s1, char *s2);
void	ft_error(char *str, char *c);
char	*ft_strjoin_ex(char *s1, char *s2);
void	ft_readline(int sig);
char	*ft_strchr(char *s, int c);
void	ft_readline(int sig);
void	ft_check_exit(t_env *env, int status);
void	ft_putstr_fd(char *str, int fd);
void	builting1(t_parc *parc, t_env	**env);
void	execute_m_cmd(t_parc *parcer, t_env *env);
char	*quotes_remover(char *input);
void	execute_cmd(t_parc *parcer, t_env *env);
int		ft_isalpha(int c);
void	builting_m_cmd(t_parc *parc, t_env	**env);
char	*ft_itoa(int n);
t_env	*ft_lstnew_env(char *key, char *content);
int		ft_lstsize_env(t_env *lst);
void	lst_clear_env(t_env *env);
char	*ft_strrchr(char *s, int c);
char	*get_chars(char *string, int index);
t_env	*ft_lstlast_env(t_env *lst);
void	lstadd_back_env(t_env **lst, t_env *new);
int		ft_atoi(const char *str);
char	**env_empty(void);
void	envi(char **env, t_env **head);
int		is_sorted(t_env *exp);
t_env	*copy_list(t_env *env);
t_env	*sorted_env(t_env *exp);
void	env(t_env *head, char *str, t_parc *parc);
int		node_existences(t_env *env, char *key);
int		equal_num(char *input);
int		parsing(char *input);
void	add_var(t_env **env, char **str);
void	unset(t_env **env, char **str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		fun(char *input, char c);
void	echo(t_parc *parc);
void	cd(char **str, t_env **env);
void	pwd(char **str, t_parc *parc);
t_env	*lstch_env(t_env *head, char *key);

#endif
