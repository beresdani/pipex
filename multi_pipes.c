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

void	child_processes(t_plist **lst, t_data *data, int ind)
{
	if (ind == 0)
		first_child_process(lst, data, ind);
	else if (ind != data->pipes)
		multi_child_process(lst, data, ind - 1);
	else
		last_child_process(lst, data, ind);
	exit(EXIT_SUCCESS);
}

void	multi_parent(t_plist *lst)
{
	t_plist	*node;

	node = lst;
	while (node != NULL)
	{
		close (node->fd[0]);
		close (node->fd[1]);
		node = node->next;
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
			free_array(data->dirs);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	node->pid = fork();
	if (node->pid == -1)
		return ;
	add_pipe_node(lst, node);
	if (node->pid == 0)
		child_processes(lst, data, ind);
}

int	multi_pipe(int pipes, char **argv, char **env, int argc)
{
	int		i;
	int		ex;
	t_plist	*lst;
	t_data	data;		

	ex = 0;
	set_data(&data, pipes, argv, env, argc);
	if (data.path == NULL)
		path_error(&data);
	check_args(&data, &ex);
	dirs_calloc(&data);
	i = 0;
	lst = NULL;
	check_commands(&data, &ex);
	while (i < pipes + 1)
	{
		pipe_fork(&lst, &data, i);
		i++;
	}
	multi_parent(lst);
	free_list(lst);
	free_array(data.dirs);
	return (0);
}
