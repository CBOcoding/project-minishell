#include "minishell.h"

// bool	checking_envp_new(char *str, char ***envp_new)
// {
// 	int		i;
// 	char	*equal;

// 	i = 0;
// 	while ((*envp_new)[i])
// 	{
// 		equal = ft_strchr((*envp_new)[i], '=');
// 		if (equal && ft_strcmp(str, equal + 1) == SUCCESS)
// 				return (true);
// 		i++;
// 	}
// 	return (false);
// }

// int	builtin_echo(char **argv, t_token *token)
// {
// 	int i;
// 	int newline;
// 	// bool check;

// 	i = 1;
// 	newline = 1;
// 	// check = false;
	
// 	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
// 	{
// 		newline = 0;
// 		i++;
// 	}

// 	// if (argv[i] && argv[i + 1])
// 	// 	check = checking_envp_new(argv[i + 1], envp_new);

// 	// Se non ci sono argomenti, stampa solo newline
// 	if (!argv[i])
// 	{
// 		if (newline)
// 			printf("\n");
// 		return (SUCCESS);
// 	}
// 	while (argv[i])
// 	{
// 		printf("%s", argv[i]);
// 		if (argv[i + 1] && 
// 			(argv[i][0] != '\'') && 
// 			(argv[i + 1][0] != '\'') &&
// 			(argv[i + 1][0] != '$') && token->flag_env_var_in_word == true)
// 				printf(" ");
// 		i++;
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (SUCCESS);
// }


int	builtin_echo(char **argv, t_token *token)
{
	int i = 1;
	int newline = 1;

	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
		token = token->next; // salta "echo"
		token = token->next; // salta "-n"
	}
	else
		token = token->next; // salta "echo"

	while (argv[i] && token)
	{
		printf("%s", argv[i]);

		if (argv[i + 1]) // se c'è un argomento dopo
		{
			if (token->skip_space > 0)
				token->skip_space--; // consuma il salto
			else
				printf(" "); // stampa spazio normalmente
		}

		i++;
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
