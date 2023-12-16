#include "pipex.h"

void	first_child_process(char **argv, s_data *data, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;

	args1 = ft_split(argv[ind], 32);
	directory = get_dir(path, args1[0]);
	close(data->fd[0][0]);
	fd_inf = open("infile", O_RDONLY);
	if (fd_inf == -1)
	{
		free_array(args1);
		free(args1);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(data->fd[0][1], STDOUT_FILENO);
	close(fd_inf);
	close(data->fd[0][1]);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_child_process(char **argv, s_data *data, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;

	args1 = ft_split(argv[ind], 32);
	directory = get_dir(path, args1[0]);
	close(data->fd[0][0]);
	fd_inf = open("infile", O_RDONLY);
	if (fd_inf == -1)
	{
		free_array(args1);
		free(args1);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(data->fd[1][1], STDOUT_FILENO);
	close(fd_inf);
	close(data->fd[1][1]);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_parent_process(char **argv, s_data *data, char *path, char **envp, int ind)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;

	args2 = ft_split(argv[ind], 32);
	directory2 = get_dir(path, args2[0]);
	wait(NULL);
	close(data->fd[1][1]);
	fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		free_array(args2);
		free(args2);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(data->fd[1][0], STDIN_FILENO);
	close(data->fd[1][0]);
	close(fd_outf);
	if (execve(directory2, args2, envp) == -1)
	{
		free_array(args2);
		free(args2);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}

int	multi_pipe(int pipes, char **argv, char **env)
{
	char	*path;
	int		i;
	s_data	data;

	data.pipes = pipes;
	path = get_path(env);
	i = 0;
	while (i < pipes)
	{
		if (pipe(data.fd[i]) == -1)
			return (1);
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (2);
		i++;
	}
	if (data.pid[i] == 0)
		multi_child_process(argv, &data, path, env, i + 2);
    return (0);
}
		