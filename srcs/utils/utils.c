#include "minishell.h"

static	unsigned int	ft_arraysize(int number)
{
	unsigned int		length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	number;
	unsigned int	length;

	length = ft_arraysize(n);
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		number = -n;
	}
	else
		number = n;
	if (number == 0)
		string[0] = '0';
	string[length] = '\0';
	while (number != 0)
	{
		string[length - 1] = (number % 10) + '0';
		number = number / 10;
		length--;
	}
	return (string);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	x;
	size_t	y;

	substring = (char *) malloc ((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s[x] != '\0')
	{
		if (x >= start && y < len)
		{
			substring[y] = s[x];
			y++;
		}
		x++;
	}
	substring[y] = '\0';
	return (substring);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n && (s1[x] != '\0' || s2[x] != '\0'))
	{
		if ((unsigned char)s1[x] != (unsigned char)s2[x])
		{
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		}
		x++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] != c))
	{
		i++;
	}
	if (s[i] != c)
		return (NULL);
	else
		return ((char *)s + i);
}
