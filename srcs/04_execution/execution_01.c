#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char	*the_path_list(char **path_list, char *cmd)
{
	int		i;
	char	*building_path;
	char	*full_path;

	i = 0;
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

char	*find_executable(char *cmd, char **envp)
{
	int		path_position;
	char	**path_split;
	char	**path_list;

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
	return (the_path_list(path_list, cmd));
}

int	execute_pipeline(t_pipeline *pipeline, char **envp_new, t_token *token)
{
	int		fd[2];
	int		input_fd;
	pid_t	pid;
	int		status;

	input_fd = 0;
	status = 0;
	while (pipeline->i_pipeline < pipeline->cmd_count)
	{
		if (pipeline_error(pipeline->i_pipeline, pipeline, fd) == 1)
			return (1);
		pid = fork();
		if (fork_error(pid) == 1)
			return (1);
		if (pid == 0)
		{
			pid_zero(input_fd, pipeline->i_pipeline, fd, pipeline);
			status = handle_command(pipeline->commands[pipeline->i_pipeline], &envp_new, 0, token);
			exit(status);//qui abbiamo un leak?? il figlio libera tutto prima di uscire??
		}
		final_checks(&input_fd, pipeline->i_pipeline, pipeline, fd);
		pipeline->i_pipeline++;
	}
	status = waiting(status);
	return (WEXITSTATUS(status));
}
