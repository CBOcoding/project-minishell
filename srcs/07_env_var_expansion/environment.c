#include "minishell.h"

static char	*handler_env_value(const char *key, char **envp)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == SUCCESS && \
			envp[i][ft_strlen(key)] == '=')
		{
			val = ft_strdup(envp[i] + ft_strlen(key) + 1);
			break ;
		}
		i++;
	}
	if (!val)
		val = ft_strdup("");
	return (val);
}

static void merge_adjacent_tokens(t_token **tokens)
{
    t_token *current;
    t_token *next;
    char    *merged;

    if (!tokens || !*tokens)
        return;
    
    current = *tokens;
    while (current && current->next)
    {
        next = current->next;
        
        // Merge tokens if they have the same quote status
        // OR if one has skip_space flag set
        if ((current->status != DEFAULT && current->status == next->status) ||
            ((current->type == WORD || current->type == ENV_VAR) &&
             (next->type == WORD || next->type == ENV_VAR) &&
             (current->skip_space > 0)))
        {
            merged = ft_strjoin(current->value, next->value);
            free(current->value);
            current->value = merged;
            
            // Preserve skip_space flag from the next token
            if (next->skip_space > 0)
                current->skip_space = next->skip_space;
                
            current->next = next->next;
            free(next->value);
            free(next);
        }
        else
            current = current->next;
    }
}

static char	*expand_pid_sequence(const char *key)
{
	char	*pid_str;
	char	*result;
	char	*tmp;
	int		j;

	pid_str = ft_itoa(getpid());
	result = ft_strdup("");
	j = 0;
	while (key[j])
	{
		tmp = result;
		result = ft_strjoin(result, pid_str);
		free(tmp);
		j++;
	}
	free(pid_str);
	return (result);
}

char	*get_env_var_value(const char *key, char **envp, int last_exit_status)
{
	char	*val;

	val = NULL;
	if (strcmp(key, "?") == 0)
		val = ft_itoa(last_exit_status);
	else if (key[0] == '$' && ft_strspn(key, "$") == ft_strlen(key))
		val = expand_pid_sequence(key);
	else if (*key == '\0')
		val = ft_strdup("$");
	else
		val = handler_env_value(key, envp);
	return (val);
}

void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status)
{
	t_token	*current;
	t_token	*prev;
	char	*key;
	char	*val;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == ENV_VAR && current->status != SQUOTE)
		{
			key = current->value + 1;
			val = get_env_var_value(key, envp, last_exit_status);
			free(current->value);
			current->value = val;
			current->type = WORD;
			if (prev && prev->skip_space > 0)
				current->skip_space = prev->skip_space;
		}
		prev = current;
		current = current->next;
	}
	merge_adjacent_tokens(&tokens);
}
