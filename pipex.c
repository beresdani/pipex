/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2023/12/13 15:03:06 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	(void) argv;
	int	fd[2];
	int	pid;
	int	fd_inf;
	int	fd_outf;
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
		close(fd[0]);
		fd_inf = open("infile", O_RDONLY);
		if (fd_inf == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
		dup2(fd_inf, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd_inf);
		close(fd[1]);
		if (execve("/usr/bin/grep", args1, NULL) == -1)
		{
            perror("execve");
            exit(EXIT_FAILURE);
        }
		/*
		args1 = ft_split(argv[1], 32);
		ft_printf("%s", args1[0]);*/
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd_outf, STDOUT_FILENO);
		fprintf(stderr, "test3\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd_outf);
		
		/*args2 = ft_split(argv[2], 32);*/
		if (execve("/usr/bin/wc", args2, NULL) == -1)
			perror("Could not execve");
		
	}
	close(fd[0]);
	close(fd[1]);
	
	return(0);

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