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
	int	infile;
	int	outfile;
	if (argc != 5)
	{
		printf("Wrong input.");
		return (1);
	}
	
	if (pipe(fd) == -1)
		return (1);

	int	id = fork();
	if (id == -1)
		return (2);
	if (id == 0)
	{
		infile = open("infile.txt", O_WRONLY);
		close(fd[1]);
		printf("Type a number:");
		read(fd[0], &infile, sizeof(int));
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		write(fd[1], &y, sizeof(int));
		printf
		close(fd[1]);
	}
}