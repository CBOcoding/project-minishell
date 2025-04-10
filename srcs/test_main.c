#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

// Declare the function from execution_01.c
int execute_command(t_cmd *cmd, char **envp);

int main(int argc, char **argv, char **envp)
{
    t_cmd test_cmd;
    char *args[3];

    (void)argc;
    (void)argv;

    // Simulate: ls -l > out.txt
    args[0] = "/bin/ls";    // Full path to ls (hardcoded for now)
    args[1] = "-l";
    args[2] = NULL;

    test_cmd.argv = args;
    test_cmd.infile = NULL;
    test_cmd.outfile = "out.txt";
    test_cmd.append = 0; // Use > (not >>)

    // Execute the command
    if (execute_command(&test_cmd, envp) == 0)
        printf("Command executed successfully.\n");
    else
        printf("Command failed.\n");

    return (0);
}
