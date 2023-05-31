
#include "mini.h"

char	*ft_strjoin_path(char *s1, char *s2)
{
	int		a;
	int		i;
	int		l;
	char	*ptr;

	i = 0;
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
	i = 0;
	while (s2[i])
	{
		ptr[l++] = s2[i++];
	}
	ptr[l] = '\0';
	return (ptr);
}

char	**ft_get_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (ft_split1(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

void	execute_cmd(t_parc *parcer, t_env *env)
{
	pid_t	id;
	char	**path1;
	char	*str;
	int		i;

	i = 0;
	str = parcer->content[0];
	id = fork();
	if (id == 0)
	{
		if (parcer->out != 1)
			dup2(parcer->out, 1);
		if (parcer->in != 0)
			dup2(parcer->in, 0);
		printf("%d\n", parcer->in);
		printf("%d\n", parcer->out);
		path1 = ft_get_path(env);
		while (path1[i])
		{
			if (ft_strchr(parcer->content[0], '/') == 0)
				str = ft_strjoin_path(path1[i], parcer->content[0]);
			if (access(str, F_OK) == 0)
				break ;
			free(str);
			str = NULL;
			i++;
		}
		if (str == NULL)
			return (printf("commende not found\n"), exit(127));
		else if (execve(str, parcer->content, NULL) < 0)
			perror("execve");
	}
	else
		waitpid(id, &i, 0);
}
