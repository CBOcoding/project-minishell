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

void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status)
{
	char	*key;
	char	*val;
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == ENV_VAR && current->status != SQUOTE)
		{
			key = current->value + 1;
			if (ft_strcmp(key, "?") == 0)
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
		}
		current = current->next;
	}
}
