#include "minishell.h"

static	char	*copy_word(const char *s, int len)
{
	int		x;
	char	*word;

	x = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (x < len)
	{
		word[x] = s[x];
		x++;
	}
	word[len] = '\0';
	return (word);
}

static	int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
		{
			s++;
		}
		if (*s != '\0')
		{
			count++;
			while (*s != c && *s != '\0')
			{
				s++;
			}
		}
	}
	return (count);
}

static	char	**free_pointers(char **array, int x)
{
	while (x > 0)
		free(array[--x]);
	free(array);
	return (NULL);
}

static	char	**filling(char **array, char const *s, char c)
{
	int			len;
	int			x;

	x = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			len = 0;
			while (*s != c && *s != '\0')
			{
				s++;
				len++;
			}
			array[x] = copy_word(s - len, len);
			if (array[x] == NULL)
				return (free_pointers(array, x));
			x++;
		}
	}
	array[x] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**array;

	word_count = count_words(s, c);
	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	if (filling(array, s, c) == NULL)
		return (NULL);
	return (array);
}
