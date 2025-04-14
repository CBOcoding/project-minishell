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
#include <sys/wait.h>   // waitpid
#include <fcntl.h>      // open
#include <stdio.h>      // perror

int execute_command(t_cmd *cmd, char **envp)
{
    pid_t pid;
    int status;
    int infile_fd;
    int outfile_fd;

    pid = fork(); // Step 1: Create child process
    if (pid < 0)
    {
        perror("fork"); // fork failed
        return (1);
    }

    if (pid == 0) // Child process
    {
        // Step 2: Handle input redirection
        if (cmd->infile)
        {
            infile_fd = open(cmd->infile, O_RDONLY);
            if (infile_fd < 0)
            {
                perror(cmd->infile); // show which file caused the error
                exit(1); // exit the child with error
            }
            if (dup2(infile_fd, STDIN_FILENO) < 0)
            {
                perror("dup2 (infile)");
                close(infile_fd);
                exit(1);
            }
            close(infile_fd); // not needed anymore
        }

        // Step 3: Handle output redirection
        if (cmd->outfile)
        {
            int flags = O_WRONLY | O_CREAT;
            if (cmd->append)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;

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

        // Step 4: Execute command
        execve(cmd->argv[0], cmd->argv, envp);

        // If execve fails:
        perror("execve");
        exit(127); // common code for command not found
    }

    // Parent process: wait for child
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return (1);
    }

    return (WEXITSTATUS(status)); // return child exit code
}
