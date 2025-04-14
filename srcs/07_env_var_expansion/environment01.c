#include "minishell.h"
#include <signal.h> // for sig_atomic_t


extern volatile sig_atomic_t g_signal; // already declared in signals.h

void expand_env_vars(t_token *tokens, char **envp, int last_exit_status)
{
    t_token *curr = tokens;
    char *key;
    char *val;

    (void)envp; // if not used, avoid unused var warning

    while (curr)
    {
        // Step-by-step logic will go here
		if (curr->type == ENV_VAR && curr->value && curr->value[0] == '$')
        {
            key = curr->value + 1; // skip '$'

            if (ft_strcmp(key, "?") == SUCCESS)
                val = ft_itoa(last_exit_status); // expand $?
            else
                val = getenv(key); // fetch env var

            free(curr->value);
            if (val)
                curr->value = ft_strdup(val);
            else
                curr->value = ft_strdup(""); // if not found, empty string
        }
        curr = curr->next;
    }
}
