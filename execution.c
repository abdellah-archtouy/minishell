
#include "mini.h"

char	*ft_strjoin_path(char *s1, char *s2)
{
	int		a;
	int		i;
	int		l;
	int		t;
	char	*ptr;

	i = 0;
	t = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	a = ft_strlen(s1) + ft_strlen(s2) + 2;
	ptr = (char *)malloc(sizeof(char) * a);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[l++] = s1[i++];
	}
	ptr[l++] = '/';
	while (s2[t])
	{
		ptr[l++] = s2[t++];
	}
	ptr[l] = '\0';
	free(s1);
	return (ptr);
}

void	execute_cmd(t_parc *parcer)
{
	pid_t	id;
	char	**path1;
	char	*str;
	int		i;

	i = 0;
	id = fork();
	if (id == 0)
	{
		dup2(parcer->out, 1);
		dup2(parcer->in, 0);
		path1 = ft_split1(getenv("PATH"), ':');
		while (path1[i])
		{
			str = ft_strjoin_path(path1[i], parcer->content[0]);
			if (access(str, F_OK) == 0)
				break ;
			free(str);
			str = NULL;
			i++;
		}
		if (execve(str, parcer->content, NULL) < 0)
			perror("execve");
	}
	waitpid(id, &i, 0);
}
