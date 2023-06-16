#include "mini.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*ft_get_char(char *str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	(void)str;
	str1 = malloc(2);
	str1[i++] = c;
	str1[i] = '\0';
	return (str1);
}
