/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:50 by dberes            #+#    #+#             */
/*   Updated: 2023/12/18 16:13:00 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	fd_closer(int ind, t_data **data)
{
	int		i;
	int		pipes;
	t_data	*node;

	i = 0;
	
	node = *data;
	pipes = list_size(data);
	while (i < pipes)
	{
		if (ind == 0)
			close(node->fd[0]);
		else if (ind == pipes)
			close(node->fd[1]);
		else
		{
			close(node->fd[1]);
			close(node->next->fd[0]);
		}
		if (ind < pipes && i != ind && i != ind + 1)
		{
			close(node->fd[0]);
			close(node->fd[1]);
		}
		if (node->next != NULL)
			node = node->next;
		i++;
	}
}

void	first_child_process(char **argv, t_data **data, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;
	t_data	*node;

	node = *data;
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
	dup2(node->fd[1], STDOUT_FILENO);
	close(fd_inf);
	close(node->fd[1]);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_child_process(char **argv, t_data **data, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	t_data	*node;
	int		i;

	i = 0;
	node = *data;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	args1 = ft_split(argv[ind + 2], 32);
	directory = get_dir(path, args1[0]);
	fd_closer(ind, data);
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	close(node->fd[0]);
	close(node->fd[1]);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	last_child_process(char **argv, t_data **data, char *path, char **envp, int ind)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;
	t_data	*node;
	int		i;

	i = 0;
	node = *data;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	args2 = ft_split(argv[ind + 2], 32);
	directory2 = get_dir(path, args2[0]);
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
	dup2(node->fd[0], STDIN_FILENO);
	close(node->fd[0]);
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
	t_data	**data;
	t_data	*node;
	
	path = get_path(env);
	i = 0;
	data = (t_data **)malloc(sizeof(t_data *));
	*data = NULL;
	while (i < pipes)
	{
		node = (t_data *)malloc(sizeof(t_data));
		if (node == NULL)
			return(0);
		*node = (t_data){0};
		if (pipe(node->fd) == -1)
			return (1);
		node->pid = fork();
		if (node->pid == -1)
			return (2);
		add_pipe_node(data, node);
		if (node->pid == 0)
    	{
        // Child process
        	if (i == 0)
            	first_child_process(argv, data, path, env, i);
        	else if (i != pipes - 1)
            	multi_child_process(argv, data, path, env, i - 1);
			else
				last_child_process(argv, data, path, env, pipes);
        	exit(EXIT_SUCCESS); // Make sure child exits after its work
    	}
    	i++;
	}
	i = 0;
	while (i < pipes)
	{	
		node = *data;
		waitpid(node->pid, NULL, 0);
		node = node->next;
		i++;
	}
    return (0);
}
		
