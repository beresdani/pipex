/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2024/01/02 21:57:32 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd[2], t_data *data, int ind)
{
	char	**args1;
	int		fd_inf;

	args1 = ft_split(data->argv[ind], 32);
	if (!args1)
		free_exit_single(args1, data, 4);
	close(fd[0]);
	fd_inf = open(data->argv[1], O_RDONLY);
	if (fd_inf == -1)
	{
		free_array(args1);
		perror("pipex: failed to open infile");
		close(fd[1]);
		close(fd_inf);
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd_inf);
	close(fd[1]);
	if (execve(data->dirs[0], args1, data->env) == -1)
		free_exit_single(args1, data, 1);
}

void	parent_process(int fd[2], t_data *data, int ind)
{
	int		fd_outf;
	char	**args2;

	args2 = ft_split(data->argv[ind], 32);
	if (!args2)
		free_exit_single(args2, data, 4);
	close(fd[1]);
	fd_outf = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: failed to open outfile");
		close(fd[0]);
		close(fd_outf);
		free_exit_single(args2, data, 1);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd_outf);
	if (execve(data->dirs[1], args2, data->env) == -1)
		free_exit_single(args2, data, 1);
}

int	single_pipe(char **argv, char **env)
{
	int		fd[2];
	int		pid;
	int		ex;
	t_data	data;

	ex = 0;
	data.path = get_path(env);
	data.env = env;
	data.argv = argv;
	data.argc = 5;
	file_create(&data);
	if (data.path == NULL)
		path_error(&data);
	check_args(&data, &ex);
	dirs_calloc(&data);
	check_commands(&data, &ex);
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
	if (argc == 5)
	{
		if (single_pipe(argv, env) != 0)
			return (2);
		return (0);
	}
	else
	{
		ft_printf("wrong input");
		exit(EXIT_FAILURE);
	}
}
