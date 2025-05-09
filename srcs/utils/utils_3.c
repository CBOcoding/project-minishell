#include "minishell.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i = i + 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i = i + 1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i = i + 1;
	}
	result = result * sign;
	return (result);
}

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z'));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	size_t	lens1s2;
	char	*newstring;

	lens1s2 = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc((lens1s2 + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		newstring[x + y] = s1[x];
		x++;
	}
	while (s2[y])
	{
		newstring[x + y] = s2[y];
		y++;
	}
	newstring[x + y] = '\0';
	return (newstring);
}

void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}
