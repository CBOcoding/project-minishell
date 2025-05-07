#include "minishell.h"
#include <fcntl.h>	  // open


	// //debug start
	// write(1, "HANDLE_COMMAND\n", 15);
	// for (int k = 0; (*envp_new)[k]; k++)
	// printf("ENVP_NEW[%i]=%s\n", k, (*envp_new)[k]);
	// //debug end

	int	handle_command(t_cmd *cmd, char ***envp_new, int last_exit_status, int *should_exit)
	{
		int infile_fd;
		int outfile_fd;
		int stdin_backup = -1;  // To store original stdin
		int stdout_backup = -1; // To store original stdout
		int result;
	
		if (!cmd || !cmd->argv || !cmd->argv[0] ||
				ft_strspn(cmd->argv[0], " \t") == ft_strlen(cmd->argv[0]))
			{
				fprintf(stderr, "minishell: command not found\n");
				return (127);
			}
			
			
		if (cmd->heredoc)
			handle_heredoc(cmd);
	
		// Store original stdin/stdout to restore them later
		if (cmd->infile || cmd->outfile)
		{
			stdin_backup = dup(STDIN_FILENO);
			stdout_backup = dup(STDOUT_FILENO);
		}
	
		// Input redirection
		if (cmd->infile)
		{
			infile_fd = open(cmd->infile, O_RDONLY);
			if (infile_fd < 0)
			{
				perror(cmd->infile);
				return (1);
			}
			if (dup2(infile_fd, STDIN_FILENO) < 0)
			{
				perror("dup2 (infile)");
				close(infile_fd);
				return (1);
			}
			close(infile_fd);
		}
	
		// Output redirection
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
				return (1);
			}
			if (dup2(outfile_fd, STDOUT_FILENO) < 0)
			{
				perror("dup2 (outfile)");
				close(outfile_fd);
				return (1);
			}
			close(outfile_fd);
		}
	
		// Execute the command
		if (is_builtin(cmd->argv[0]))
			result = execute_builtin(cmd->argv, envp_new, last_exit_status, should_exit);
		else
			result = execute_command(cmd, *envp_new);
	
		// Restore original stdin/stdout
		if (stdin_backup != -1)
		{
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
		}
		if (stdout_backup != -1)
		{
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdout_backup);
		}
	
		return (result);
	}


/*

!(*cmd->commands)
cmd->commands -> **
(*cmd->commands) -> * index 0
++(*cmd->commands) -> * index 1
cmd->commands[0] -> [0]

*/
