/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2023/12/14 14:28:53 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_dir(char *str, char *cmd)
{
	char	**dirs;
	char	*dir;
	int		i;

	dirs = ft_split(str, 58);
	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (access(dir, F_OK) == 0)
			return (dir);
		i++;
	}
	return (NULL);
}

void	child_process(char **argv, int fd[2], char *path, char **envp)
{
	char	**args1;
	char	*directory;
	int		fd_inf;

	args1 = ft_split(argv[2], 32);
	directory = get_dir(path, args1[0]);
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
	if (execve(directory, args1, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(char **argv, int fd[2], char *path, char **envp)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;

	args2 = (char **)malloc(sizeof(char *)*);
	args2 = ft_split(argv[3], 32);
	directory2 = get_dir(path, args2[0]);
	wait(NULL);
	close(fd[1]);
	fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd_outf);
	if (execve(directory2, args2, envp) == -1)
	{
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		pid;
	char	*path;

	if (argc != 5)
	{
		ft_printf("Wrong input.");
		return (1);
	}
	path = get_path(env);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
		child_process(argv, fd, path, env);
	else
		parent_process(argv, fd, path, env);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
