/*
expected from parsing:

typedef struct s_cmd
{
    char **argv;         // List of arguments (like {"ls", "-l", NULL})
    char *infile;        // If input redirection is used (e.g. "< file.txt")
    char *outfile;       // If output redirection is used (e.g. "> out.txt" or ">> out.txt")
    int   append;        // 0 = use ">", 1 = use ">>"
} t_cmd;


*/

#include "minishell.h"

#include <unistd.h>     // fork, execve, dup2, close
#include <stdlib.h>     // exit
#include <sys/wait.h>   // waitpid, WEXITSTATUS
#include <fcntl.h>      // open
#include <stdio.h>      // perror

int execute_command(t_cmd *cmd, char **envp)
{
    pid_t pid;
    int   status;
    int   infile_fd;
    int   outfile_fd;
    int   flags;

    // Step 1: Create a child process
    pid = fork();
    if (pid < 0)
    {
        // If fork fails, print an error and return non-zero
        perror("fork");
        return (1);
    }

    // Step 2: Child process
    if (pid == 0)
    {
        // --- Input redirection ---
        if (cmd->infile)
        {
            infile_fd = open(cmd->infile, O_RDONLY);
            if (infile_fd < 0)
            {
                perror(cmd->infile);
                exit(1);
            }
            if (dup2(infile_fd, STDIN_FILENO) < 0)
            {
                perror("dup2 (infile)");
                close(infile_fd);
                exit(1);
            }
            close(infile_fd);
        }

        // --- Output redirection ---
        if (cmd->outfile)
        {
            flags = O_WRONLY | O_CREAT;
            if (cmd->append == 1)
                flags = flags | O_APPEND;
            else
                flags = flags | O_TRUNC;

            outfile_fd = open(cmd->outfile, flags, 0644);
            if (outfile_fd < 0)
            {
                perror(cmd->outfile);
                exit(1);
            }
            if (dup2(outfile_fd, STDOUT_FILENO) < 0)
            {
                perror("dup2 (outfile)");
                close(outfile_fd);
                exit(1);
            }
            close(outfile_fd);
        }

        // --- Execute the command ---
        // argv[0] should be the full or relative path to the executable
        // argv must be NULL-terminated
        execve(cmd->argv[0], cmd->argv, envp);

        // If execve fails, we print an error and exit with 127 (command not found)
        perror("execve");
        exit(127);
    }

    // Step 3: Parent process waits for the child to finish
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return (1);
    }

    // Step 4: Return the exit status of the child process
    return (WEXITSTATUS(status));
}
