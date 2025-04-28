#include "minishell.h"

t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    ft_memset(cmd, 0, sizeof(t_cmd));
    return cmd;
}
/*
void	*ft_memset(void *s, int c, size_t len)
{
	size_t	i;
	char	*pointer;

	i = 0;
	pointer = (char *)s;
	while (i < len)
	{
		pointer[i] = c;
		i++;
	}
	return (s);
}
	char	*ft_strdup(const char *s)
{
	char	*src;
	char	*scopy;
	int		x;

	src = (char *)s;
	scopy = (char *) malloc((ft_strlen(src) + 1) * sizeof(char));
	if (scopy == NULL)
		return (NULL);
	x = 0;
	while (src[x] != '\0')
	{
		scopy[x] = src[x];
		x++;
	}
	scopy[x] = '\0';
	return (scopy);
}
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
	size_t	ft_strlen(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

*/