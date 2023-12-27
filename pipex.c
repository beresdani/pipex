/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2023/12/19 10:49:30 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
void	free_exit(int err)
{

}
*/
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	child_process(int fd[2], t_data *data, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;

	args1 = ft_split(data->argv[ind], 32);
	directory = get_dir(data->path, args1, NULL);
	close(fd[0]);
	fd_inf = open("infile", O_RDONLY);
	if (fd_inf == -1)
	{
		free_array(args1);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd_inf);
	close(fd[1]);
	if (execve(directory, args1, data->env) == -1)
	{
		free_array(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int fd[2], t_data *data, int ind)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;

	args2 = ft_split(data->argv[ind], 32);
	directory2 = get_dir(data->path, args2, NULL);
	close(fd[1]);
	fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		free_array(args2);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd_outf);
	if (execve(directory2, args2, data->env) == -1)
	{
		free_array(args2);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}

int	single_pipe(char **argv, char **env)
{
	int		fd[2];
	int		pid;
	t_data	data;

	data.path = get_path(env);
	data.env = env;
	data.argv = argv;
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
		child_process(fd, &data, 2);
	else
		parent_process(fd, &data, 3);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	pipes;

	pipes = argc - 4;
	if (argc < 5)
	{
		perror("wrong input");
    	exit(EXIT_FAILURE);
	}
	else if (argc == 5)
	{
		if (single_pipe(argv, env) != 0)
			return (2);
		return (0);
	}
	else
	{
		if (multi_pipe(pipes, argv, env) != 0)
			return (3);
		return (0);
	}
}
