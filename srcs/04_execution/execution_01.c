#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

extern volatile sig_atomic_t	g_signal;

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char	*find_executable(char *cmd, char **envp)
{
	int		path_position;
	char	**path_split;
	char	**path_list;
	char	*building_path;
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	path_position = key_exists(envp, "PATH");
	if (path_position == -1)
	{
		perror("Missing PATH");
		return (NULL);
	}
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
	while (path_list[i])
	{
		building_path = ft_strjoin(path_list[i], "/");
		full_path = ft_strjoin(building_path, cmd);
		free(building_path);
		if (access(full_path, X_OK) == 0)
		{
			free_matrix(path_list);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_matrix(path_list);
	return (NULL);
}

int execute_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		infile_fd;
	int		outfile_fd;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (1);
	}
	if (pid == 0)
	{
		if (!cmd->argv[0] || ft_strspn(cmd->argv[0], " \t") == \
			ft_strlen(cmd->argv[0]))
		{
			fprintf(stderr, "minishell: command not found\n");
			exit(127);
		}
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
		if (cmd->outfile)
		{
			int	flags = O_WRONLY | O_CREAT;
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
		char *path = find_executable(cmd->argv[0], envp);
		if (path && path != cmd->argv[0])
		{
			execve(path, cmd->argv, envp);
			free(path);
		}
		else
			execve(cmd->argv[0], cmd->argv, envp);
		perror("execve");
		exit(127);
	}
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	execute_pipeline(t_pipeline *pipeline, char **envp_new, t_token *token)
{
	int		fd[2];
	int		input_fd;
	pid_t	pid;
	int		i;
	int		status;

	input_fd = 0;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (i < pipeline->cmd_count - 1)
		{
			if (pipe(fd) == -1)
			{
				perror("Fail to create a pipe");
				return (1);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			return (1);
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (input_fd != 0)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (i < pipeline->cmd_count - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			status = handle_command(pipeline->commands[i], &envp_new, 0, token);
			exit(status);//qui abbiamo un leak?? il figlio libera tutto prima di uscire??
		}
		if (input_fd != 0)
			close(input_fd);
		if (i < pipeline->cmd_count - 1)
		{
			close(fd[1]);
			input_fd = fd[0];
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}
