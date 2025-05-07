#include "minishell.h"

int	is_argv_numeric(char **argv)
{
	int	i;

	i = 0;
	if (argv[1][i] == '-'|| argv[1][i] == '+')
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

	if (is_argv_numeric(argv)) //se non é un numero (FAILURE) entra
	{
		printf("exit: %s: numeric argument required\n", argv[1]);
		return ((unsigned char)255); //exit code 255
	}
	value = ft_atoi(argv[1]);
	return (value);
}

int	builtin_exit(char **argv, int exit_status, int *should_exit)
{
	int	i;

	i = 0;
	while (argv[i]) // Count the number of arguments in argv
		i++;
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	if (i > 2) // Check if there are too many arguments
	{
		write(2, "exit: too many arguments\n", 25);
		return (1); // Stay in shell
	}
	if (i == 2)
		exit_status = (unsigned char)exit_with_number(argv);

	*should_exit = 1;
	return (exit_status);


	// if (i == 1) // Check if there is no argument
	// {
	// 	*should_exit = 1;
	// 	write(1, "exit\n", 5);
	// 	return (0); //((unsigned char)0); //exit code 0
	// }
	// else //i = 2 ossia esiste argv[1]
	// {
	// 	exit_status = (unsigned char)exit_with_number(argv);
	// 	return (exit_status);
	// }
	// return (SUCCESS);
}
