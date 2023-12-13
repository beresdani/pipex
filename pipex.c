/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2023/12/13 14:21:16 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	(void) argv;
	int	fd[2];
	int	pid;
	int	infile;
	int	outfile;
	char	*args1[] = {"grep", "a1", NULL};
	char	*args2[] = {"wc", "-w", NULL};
	if (argc != 3)
	{
		ft_printf("Wrong input.");
		return (1);
	}
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		infile = open("infile.txt", O_WRONLY);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		/*args1 = ft_split(argv[1], 32);
		ft_printf("%s", args1[0]);*/
		if (execve("/usr/bin/grep", args1, NULL) == -1)
			perror("Could not execve");
	}
	else
	{
		outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(outfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		/*args2 = ft_split(argv[2], 32);*/
		if (execve("/usr/bin/wc", args2, NULL) == -1)
			perror("Could not execve");
	}
	close(fd[0]);
	close(fd[1]);

	/*
		waitpid(pid, NULL, 0);
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
*/
}