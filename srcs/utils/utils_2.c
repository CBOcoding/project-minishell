#include "minishell.h"

t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    ft_memset(cmd, 0, sizeof(t_cmd));
    return cmd;
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i = 0;
	size_t	j;

	while (s[i])
	{
		j = 0;
		while (accept[j] && s[i] != accept[j])
			j++;
		if (!accept[j])
			break;
		i++;
	}
	return (i);
}

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