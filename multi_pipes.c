/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:50 by dberes            #+#    #+#             */
/*   Updated: 2023/12/19 15:12:47 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_closer(int end, t_plist **lst)
{
	t_plist	*node;

	node = *lst;
	if (list_size(lst) == 1)
	{
		close (node->fd[0]);
		close (node->fd[1]);
	}
	else
	{
		while (node->next->next != NULL)
		{
			close (node->fd[0]);
			close (node->fd[1]);
			node = node->next;
		}
	}
	if (end == 1)
		close (node->fd[1]);
	else
	{
		close (node->fd[0]);
		close (node->fd[1]);
	}
}

void	first_child_process(char **argv, t_plist **lst, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;
	t_plist	*node;

	node = *lst;
	args1 = ft_split(argv[ind + 2], 32);
	directory = get_dir(path, args1[0]);
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
	fd_closer(0, lst);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_child_process(char **argv, t_plist **lst, char *path, char **envp, int ind)
{
	char	**args1;
	char	*directory;
	t_plist	*node;
	int		i;

	i = 0;
	node = *lst;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	args1 = ft_split(argv[ind + 3], 32);
	directory = get_dir(path, args1[0]);
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->next->fd[1], STDOUT_FILENO);
	fd_closer(0, lst);
	if (execve(directory, args1, envp) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	last_child_process(char **argv, t_plist **lst, char *path, char **envp, int ind)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;
	t_plist	*node;
	int		i;

	i = 0;
	node = *lst;
	while (i < ind -1)
	{
		node = node->next;
		i++;
	}
	fd_closer(1, lst);
	args2 = ft_split(argv[ind + 2], 32);
	directory2 = get_dir(path, args2[0]);
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
	close (node->fd[0]);
	close(fd_outf);
	if (execve(directory2, args2, envp) == -1)
	{
		free_array(args2);
		free(args2);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}

void	child_processes(char **argv, t_plist **lst, t_data *data, int ind)
{
	if (ind == 0)
		first_child_process(argv, lst, data->path, data->env, ind);
	else if (ind != data->pipes)
		multi_child_process(argv, lst, data->path, data->env, ind - 1);
	else
		last_child_process(argv, lst, data->path, data->env, data->pipes);
	exit(EXIT_SUCCESS); // Make sure child exits after its work
}

void	multi_parent(t_plist **lst, int pipes, int i)
{
	t_plist	*node;
	
	if (i == pipes)
		{
			node = *lst;
			while (node != NULL)
			{
				close (node->fd[0]);
				close (node->fd[1]);
				node = node->next;
			}
		}
}

void	pipe_fork(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	
	node = (t_plist *)malloc(sizeof(t_plist));
	if (node == NULL)
		return ;
	*node = (t_plist){0};
	if (ind < data->pipes)
	{
		if (pipe(node->fd) == -1)
		{
			perror("pipe");
    		exit(EXIT_FAILURE);
		}
	}
	node->pid = fork();
	if (node->pid == -1)
		return ;
	add_pipe_node(lst, node);
	if (node->pid == 0)
		child_processes(data->argv, lst, data, ind);
	else
		multi_parent(lst, data->pipes, ind);
}

int	multi_pipe(int pipes, char **argv, char **env)
{
	int		i;
	t_plist	**lst;
	t_plist	*node;
	t_data	data;		
	
	data.path = get_path(env);
	data.env = env;
	data.pipes = pipes;
	data.argv = argv;
	i = 0;
	lst = (t_plist **)malloc(sizeof(t_plist *));
	*lst = NULL;
	while (i < pipes + 1)
	{
		pipe_fork(lst, &data, i);
    	i++;
	}
	i = 0;
	node = *lst;
	while (node != NULL)
	{	
		waitpid(node->pid, NULL, 0);
		node = node->next;
		i++;
	}
    return (0);
}
		
