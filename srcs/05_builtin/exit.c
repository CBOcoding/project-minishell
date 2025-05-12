#include "minishell.h"

int	is_argv_numeric(char **argv)
{
	int	i;

	i = 0;
	if (argv[1][i] == '-' || argv[1][i] == '+')
		i++;
	if (!argv[1][i])
		return (FAILURE);
	while (argv[1][i])
	{
		if (argv[1][i] < '0' || argv[1][i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	exit_with_number(char **argv)
{
	int	value;

	if (is_argv_numeric(argv))
	{
		ft_putstr_fd("exit: \n", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		return ((unsigned char)2);
	}
	value = ft_atoi(argv[1]);
	return (value);
}

int	builtin_exit(char **argv, int exit_status, int *should_exit)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (i == 2)
		exit_status = (unsigned char)exit_with_number(argv);
	*should_exit = 1;
	return (exit_status);
}
