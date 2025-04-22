#include "minishell.h"

t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    ft_memset(cmd, 0, sizeof(t_cmd));
    return cmd;
}
