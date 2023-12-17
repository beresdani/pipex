#include "pipex.h"


void	fd_closer(int ind, s_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->pipes)
	{
		if (ind == 0)
			close(data->fd[0][0]);
		else if (ind == data->pipes)
			close(data->fd[ind -1][1]);
		else
		{
			close(data->fd[ind - 1][1]);
			close(data->fd[ind][0]);
		}
		if (ind > 0 && i != ind && i != ind -1)
		{
			close(data->fd[i][0]);
			close(data->fd[i][1]);
		}
		i++;
	}
}


void	first_child_process(char **argv, s_data *data, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;

	args1 = ft_split(argv[ind + 2], 32);
	directory = get_dir(path, args1[0]);
	fd_closer(ind, data);
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

	args1 = ft_split(argv[ind + 2], 32);
	directory = get_dir(path, args1[0]);
	fd_closer(ind, data);
	dup2(data->fd[0][0], STDIN_FILENO);
	dup2(data->fd[1][1], STDOUT_FILENO);
	close(data->fd[0][0]);
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

	args2 = ft_split(argv[ind + 2], 32);
	directory2 = get_dir(path, args2[0]);
	wait(NULL);
	fd_closer(ind, data);
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
	s_data	*data;

	data = malloc(sizeof(s_data) + pipes*sizeof(int[2]) + pipes*sizeof(pid_t));
	if (data != NULL) 
	{
        data->pipes = pipes;
		data->fd = (int(*)[2])(data + 1);
        if (data->fd == NULL) 
		{
            free(data);
            return (3);
		}
    }
	data->pipes = pipes;
	path = get_path(env);
	i = 0;
	while (i < pipes)
	{
		if (pipe(data->fd[i]) == -1)
			return (1);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (2);
		if (data->pid[i] == 0)
    	{
        // Child process
        	if (i == 0)
            	first_child_process(argv, data, path, env, i);
        	else
            	multi_child_process(argv, data, path, env, i);
        	exit(EXIT_SUCCESS); // Make sure child exits after its work
    	}
    	i++;
	}
	multi_parent_process(argv, data, path, env, pipes);	
    return (0);
}
		