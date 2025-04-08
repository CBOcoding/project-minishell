#include "minishell.h"

void	hello_minishell(void)
{
	char	*a;
	int		x;
	
	a = "hello_minishell";
	x = ft_strlen(a);
	printf("%d\n", x);
}

int	main(void)
{
	write(1, "Minishell\n", 10);
	hello_minishell();
	exit(0);
}