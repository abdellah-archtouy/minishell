
#include "mini.h"

char	*ft_strjoin(char *s1, char *s2)
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
	a = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(sizeof(char) * a);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[l++] = s1[i++];
	}
	while (s2[t])
	{
		ptr[l++] = s2[t++];
	}
	ptr[l] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_strjoin_ex(char *s1, char *s2)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	ptr = (char *)malloc(1 * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
		ptr[l++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[l++] = s2[i++];
	ptr[l] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_strjoin_wspace(char *s1, char *s2)
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
		ptr[l++] = s1[i++];
	while (s2[t])
		ptr[l++] = s2[t++];
	ptr[l++] = ' ';
	ptr[l] = '\0';
	return (ptr);
}

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
