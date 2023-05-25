
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
	return (ptr);
}