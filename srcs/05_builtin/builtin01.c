#include "minishell.h"

// nella mia libft ho strncmp, ma non ft_strcmp, quindi o misuriamo la len del comando o teniamo questa qui.
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// Check if the command is a builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "echo") == SUCCESS ||
		ft_strcmp(cmd, "cd") == SUCCESS ||
		ft_strcmp(cmd, "pwd") == SUCCESS ||
		ft_strcmp(cmd, "export") == SUCCESS ||
		ft_strcmp(cmd, "unset") == SUCCESS ||
		ft_strcmp(cmd, "env") == SUCCESS ||
		ft_strcmp(cmd, "exit") == SUCCESS
	);
}

// Simple echo implementation
int	builtin_echo(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_cd(char **argv)
{
	char *path;

	if (argv[1] == NULL)
	{
		path = getenv("HOME"); //se non c'é argomento vai alla HOME.
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 18);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0) // CHDIR return 0 if the change path goes well.
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_pwd(char **argv)
{
	char *path;

	(void)argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

int	builtin_export(char **argv, char ***envp_new)
{
	int	i;
	char *equal;
	char *key;

	i = 0;
	//parte 1, arriva il comando: export
	if (argv[1] == NULL)
	{
		while ((*envp_new)[i])
		{
			printf("%s\n", (*envp_new)[i]);
			i++;
		}
		return (0);
	}

	equal = ft_strchr(argv[1], '=');

	if (equal) //parte 3, arriva il comando: export VAR=valore
	{
		key = ft_substr(argv[1], 0, equal - argv[1]); //crea una substr con malloc.
		if (!key) //se fallisce esce e in main va liberato tutto.
			{
				perror("export: malloc failed");
				return (FAILURE);
			}
		if (!is_valid_key(key))// funzione da scrivere
		{
			print_error(argv[1]);// funzione da scrivere
			free(key);
			return (1);
		}
		replace_or_add_env(envp_new, argv[i], key); // funzione da scrivere
		free(key);
	}
	else //parte 2, arriva il comando: export VAR
	{
		if (!is_valid_key(argv[i]))
		{
			print_error(argv[i]);// funzione da scrivere
			return (1);
		}
		if (!key_exists(*envp_new, argv[i]))// funzione da scrivere
			add_env_var(envp_new, argv[i]); // aggiungi VARIABLE = vuoto
	}
	return (0);


		//parte 2, arriva il comando: export VAR
		// if (ft_strcmp(argv[1], envp_new[1]) == 0)

//controllare se gia esiste e nel caso non aggiungerla, altrimenti la creo.

		//parte 3, arriva il comando: export VAR=valore
		// if (ft_strcmp(argv[1], envp_new[1]) < 0)

//controllare se esiste e nel caso aggiornare il valore, altrimenti la creo.

		//parte 4, arriva il comando: export 1VAR=ciao IN BASH MA NON RICHIESTA
		// if (envp_new[i][1] != "_" || (envp_new[i][1] < "A" || envp_new[i][1] > "Z") || (envp_new[i][1] < "a" || envp_new[i][1] > "z"))
		// 	{
		// 		perror("Export");
		// 		return (1);
		// 	}
	//}

}

// Dispatcher
int	execute_builtin(char **argv, char ***envp_new, int *exit_status)
{
	(void)exit_status; // ci serve solo per Exit builtin

	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, envp_new));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	return (1);
}

/*
echo: Displays a line of text.
Usage: echo [-n] [string ...]
Behavior: Prints the provided strings to standard output, separated by spaces. The -n option omits the trailing newline.​

cd: Changes the current directory.
Usage: cd [directory]
Behavior: Changes the shell's current working directory to the specified path. If no directory is provided, it defaults to the value of the HOME environment variable.

pwd: Prints the current working directory.
Usage: pwd
Behavior: Outputs the absolute pathname of the current working directory.​

export: Sets environment variables.
Usage: export [name[=value] ...]
Behavior: Marks each name to be passed to child processes in the environment. If a value is provided, it assigns that value to the variable.​

unset: Removes environment variables.
Usage: unset [name ...]
Behavior: Removes each specified variable from the shell's environment.​

env: Displays the environment variables.
Usage: env
Behavior: Prints the current environment variables.​

exit: Exits the shell.
Usage: exit [n]
Behavior: Exits the shell with a status of n. If n is omitted, the exit status is that of the last command executed.
*/
