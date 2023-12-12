/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2023/12/11 18:41:35 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	infile;
	int	file2;
	int	outfile;

	if (argc != 5)
	{
		printf("Wrong input.");
		return (1);
	}
	if (pipe(fd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve()
	}
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve()
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(fd[0]);
	close(fd[1]);

		infile = open("infile.txt", O_WRONLY);
		close(fd[0]);
		write(fd[1], &y, sizeof(int));
		printf
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		printf("Type a number:");
		read(fd[0], &infile, sizeof(int));
		close(fd[0]);
	}
	file2 = dup2(infile, 1);
	if (id != 0)
		wait();

}