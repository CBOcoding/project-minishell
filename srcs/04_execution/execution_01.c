/*
expected from parsing:

typedef struct s_cmd
{
	int		append;        // For >> redirection - 0 = use ">", 1 = use ">>"
	int		heredoc;       // For << heredoc
	char	**argv;       // Command + arguments (e.g., ["ls", "-l", NULL])
	char	*infile;      // Input redirection file - If input redirection is used (e.g. "< file.txt")
	char	*outfile;     // Output redirection file - If output redirection is used (e.g. "> out.txt" or ">> out.txt")
	char	*delimiter;   // Heredoc delimiter
} t_cmd;

typedef struct s_pipeline
{
	int		cmd_count;     // Number of commands
	t_cmd	**commands;  // Array of commands
}	t_pipeline;
*/
#include "minishell.h"
#include <unistd.h>	  // fork, execve, dup2, close
#include <stdlib.h>	  // exit
#include <sys/wait.h> // waitpid
#include <fcntl.h>	  // open
#include <stdio.h>	  // perror

void free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char *find_executable(char *cmd, char **envp)
{
	int	path_position;
	char	**path_split;
	char	**path_list;
	char	*building_path;
	char	*full_path;
	int	i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);

	path_position = key_exists(envp, "PATH");
	if (path_position == -1)
	{
		perror("Missing PATH");
		return (NULL);
	}
	//prendo PATH e rimuovo PATH=, mi tengo la seconda parte dove ho la lista delle path
	path_split = ft_split(envp[path_position], '=');
	if (!path_split || !path_split[1])
	{
		free_matrix(path_split);
		return (NULL);
	}
	path_list = ft_split(path_split[1], ':');
	free_matrix(path_split);
	if (!path_list)
        return (NULL);
	// adesso ho path_list con tutti i path da controllare.
	while (path_list[i])
	{
		building_path = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(building_path, cmd);
		free(building_path);

		if(access(full_path, X_OK) == 0)
		{
			free_matrix(path_list);
			return (full_path); //trovato
		}
		free(full_path);
		i++;
	}
	free_matrix(path_list);
	return (NULL);
}

int execute_command(t_cmd *cmd, char **envp) //add PATH section
{
	pid_t	pid;
	int		status;
	int		infile_fd;
	int		outfile_fd;

	pid = fork(); // Step 1: Create child process
	if (pid < 0)
	{
		perror("fork error"); // fork failed
		return (1);
	}

	if (pid == 0) // Child process
	{
		// // Step 1: Handle heredoc (se presente)
		// if (cmd->heredoc)
		// handle_heredoc(cmd);

		// Step 2: Handle input redirection
		if (cmd->infile)
		{
			infile_fd = open(cmd->infile, O_RDONLY);
			if (infile_fd < 0)
			{
				perror(cmd->infile); // show which file caused the error
				exit(1);			 // exit the child with error
			}
			if (dup2(infile_fd, STDIN_FILENO) < 0)
			{
				perror("dup2 (infile)");
				close(infile_fd);
				exit(1);
			}
			close(infile_fd);
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
		//Pre step 4: Trova il percorso dell'eseguibile
		char *path = find_executable(cmd->argv[0], envp);
		if (path && path != cmd->argv[0])
		{
			execve(path, cmd->argv, envp);
			free(path);
		}
		else
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

int	execute_pipeline(t_pipeline *pipeline, char **envp_new)
{
	int fd[2];        // file descriptor della pipe
	int input_fd;    // input corrente, all'inizio è STDIN
	pid_t pid;        // pid dei figli
	int i;        // indice dei comandi
	int status;       // per waitpid

	input_fd = 0;// input corrente, all'inizio è STDIN
	i = 0;
	// if (pipeline->cmd_count == 1)
	// 	return(handle_command(pipeline->commands[0], &envp_new, 0));
	// else
		while (i < pipeline->cmd_count)
		{
			// Se non è l'ultimo comando, crea una pipe
			if (i < pipeline->cmd_count - 1)
			{
				if (pipe(fd) == -1)
				{
					perror("Fail to create a pipe");
					return (1);//exit function to free everything!!!!!
				}
			}
		
			// fork per creare il figlio
			pid = fork();
			if (pid < 0)
			{
				perror("fork error"); // fork failed
				return (1);
			}

			if (pid == 0) // figlio
			{
				// Se non è il primo comando, duplica input_fd su STDIN
				if (input_fd != 0)
				{
					dup2(input_fd, STDIN_FILENO);
					close(input_fd);
				}
				// Se non è l'ultimo comando, duplica fd[1] su STDOUT
				if (i < pipeline->cmd_count - 1)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[0]);
					close(fd[1]);
				}
		
				// Esegui il comando
				status = handle_command(pipeline->commands[i], &envp_new, 0);
				exit (status);
				// Se exec fallisce
				// exit(1);//exit function to free everything!!!!!
			}
		
			// PADRE: gestisce file descriptor
			if (input_fd != 0)
				close(input_fd);
		
			if (i < pipeline->cmd_count - 1)
			{
				close(fd[1]);
				input_fd = fd[0]; // il prossimo comando leggerà da qui
			}
			i++;
		}
	while (waitpid(-1, &status, 0) > 0)
		;
	return (WEXITSTATUS(status));
		
}