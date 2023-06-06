#include "mini.h"

static int	word_count(const char *s)
{
	int	j;

	j = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s && (*s != ' ' && *s != '\t'))
			j++;
		while (*s && (*s != ' ' && *s != '\t'))
			s++;
	}
	return (j);
}

static int	size(const char *s)
{
	int	j;

	j = 0;
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	while (*s && (*s != ' ' && *s != '\t'))
	{
		j++;
		s++;
	}
	return (j);
}

static char	*allocation_of_words(const char *s)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(size(s) * sizeof(char) + 1);
	if (!word)
		return (NULL);
	while (*s && (*s != ' ' && *s != '\t'))
		word[i++] = *s++;
	word[i] = '\0';
	return (word);
}

static void	frees(char **ptr, int j)
{
	while (j > 0)
	{
		free(ptr[j - 1]);
		j--;
	}
	free(ptr);
}

char	**ft_split(char const *s)
{
	int		j;
	int		i;
	char	**ptr;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (word_count(s) + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i])
			ptr[j++] = allocation_of_words(&s[i++]);
		if (j > 0 && !ptr[j - 1])
			return (frees(ptr, j), NULL);
		while (s[i] && (s[i] != ' ' && s[i] != '\t'))
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
