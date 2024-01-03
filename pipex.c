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
	int		ex;

	ex = 0;
	close(fd[0]);
	args1 = ft_split(data->argv[ind], 32);
	if (!args1)
	{
		close(fd[1]);
		free_exit_malloc(args1, data);
	}
	fd_inf = open(data->argv[1], O_RDONLY);
	if (fd_inf == -1)
	{
		ft_printf("pipex: %s: No such file or directory\n", data->argv[1]);
		close(fd[1]);
		ex = 2;
	}
	if (data->path == NULL || args1[0] == NULL)
	{
		close(fd[1]);
		ex = 3;
	}
	if (ex != 3)
	{
		dirs_calloc(data);
		check_commands(args1, data, 2);
	}
	if (ex != 0)
		free_exit_single(args1, data, ex);
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
	int		ex;

	ex = 0;
	close(fd[1]);
	args2 = ft_split(data->argv[ind], 32);
	if (!args2)
	{
		close(fd[0]);
		free_exit_malloc(args2, data);
	}
	fd_outf = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: failed to open outfile");
		close(fd[0]);
		ex = 2;
	}
	if (data->path == NULL || args2[0] == NULL)
	{
		close(fd[0]);
		ex = 3;
	}
	if (ex != 3)
	{
		dirs_calloc(data);
		check_commands(args2, data, 3);
	}
	if (ex != 0)
		free_exit_single(args2, data, ex);
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
	t_data	data;

	set_data(&data, 1, argv, env);
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
