#include "minishell.h"
#include <signal.h> // for sig_atomic_t

extern volatile sig_atomic_t g_signal; // already declared in signals.h

static char	*handler_env_value(char *key, char **envp)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == SUCCESS && envp[i][ft_strlen(key)] == '=')
		{
			val = ft_strdup(envp[i] + ft_strlen(key) + 1);
			break;
		}
		i++;
	}
	if (!val)
		val = ft_strdup("");
	return (val);
}
static void merge_adjacent_tokens(t_token **tokens)
{
    t_token *current, *next;

    
    if (!tokens || !*tokens)
        return;
    
    current = *tokens;

    
    while (current && current->next)
    {
        next = current->next;
        
        // If both tokens are in the same quoted context, merge them
        if (current->status != DEFAULT && current->status == next->status)
        {
            // Merge values
            char *merged = ft_strjoin(current->value, next->value);
            free(current->value);
            current->value = merged;
            
            // Remove the next token from the list
            current->next = next->next;
            free(next->value);
            free(next);
            
            // Don't advance current, as we may need to merge with the next token too
        }
        else
        {

            current = current->next;
        }
    }
}


// void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status)
// {
// 	char	*key;
// 	char	*val;
// 	t_token	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == ENV_VAR && current->status != SQUOTE)
// 		{
// 			key = current->value + 1; //salta dollaro
// 			if (strcmp(key, "?") == 0)
// 				val = ft_itoa(last_exit_status);
// 			else if (ft_strcmp(key, "$") == SUCCESS)
// 				val = ft_strdup("$$");
// 			else if (*key == '\0')
// 				val = ft_strdup("$");
// 			else
// 				val = handler_env_value(key, envp);
// 			free(current->value);
// 			current->value = val;
// 			current->type = WORD;
// 		}
// 		current = current->next;
// 	}
// 	merge_adjacent_tokens(&tokens);
// }

void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status)
{
	char	*key;
	char	*val;
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == ENV_VAR && current->status != SQUOTE)
		{
			key = current->value + 1; // salta il $
			if (strcmp(key, "?") == 0)
				val = ft_itoa(last_exit_status);
			else if (ft_strcmp(key, "$") == SUCCESS)
				val = ft_strdup("$$");
			else if (*key == '\0')
				val = ft_strdup("$");
			else
				val = handler_env_value(key, envp);

			free(current->value);
			current->value = val;
			current->type = WORD;

			// Propaga skip_space se il token precedente lo aveva
			if (prev && prev->skip_space > 0)
				current->skip_space = prev->skip_space;
		}
		prev = current;
		current = current->next;
	}
	merge_adjacent_tokens(&tokens);
}
