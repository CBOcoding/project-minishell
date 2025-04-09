#include "minishell.h"

int has_closed_quotes(const char *str)
{
    int i;
    char quote;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
        {  
            quote = str[i++];
            while(str[i])
            {
                if(str[i] == quote)
                    return (SUCCESS);
                i++;
            }  
        }
        i++;
    }
    return (FAILURE);
}

int ft_strcmp(const char *main, char *compared)
{
    int i;

    i = 0;
    while(compared[i] && main[i])
    {
        if(compared[i] != main[i])
            return (FAILURE);
        i++;
    }
    if (main[i] || compared[i])
        return (FAILURE);
    return (SUCCESS);
}