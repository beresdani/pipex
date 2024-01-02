/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:32 by dberes            #+#    #+#             */
/*   Updated: 2024/01/02 23:58:51 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(t_plist **lst, t_data *data, int ind)
{
	int		fd_inf;
	t_plist	*node;
	char	**args;

	node = *lst;
	args = ft_split(data->argv[ind + 2], 32);
	fd_inf = open(data->argv[1], O_RDONLY);
	if (fd_inf == -1)
	{
		perror("bash: infile");
		fd_closer(0, lst);
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	close(fd_inf);
	fd_closer(0, lst);
	printf("%s\n", data->dirs[ind]);
	if (execve(data->dirs[ind], args, data->env) == -1)
		free_exit(args, data, 1);
}

void	multi_child_process(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	char	**args;

	node = *lst;
	node = get_to_node(node, ind);
	dup2(node->fd[0], STDIN_FILENO);
	if (dup2(node->next->fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
		close(node->fd[0]);
		fd_closer(0, lst);
		exit(EXIT_FAILURE);
	}
	fd_closer(0, lst);
	args = ft_split(data->argv[ind + 3], 32);
	if (!args)
		free_exit(args, data, 4);
	if (execve(data->dirs[ind + 1], args, data->env) == -1)
		free_exit(args, data, 1);
}

void	last_child_process(t_plist **lst, t_data *data, int ind)
{
	int		fd_outf;
	t_plist	*node;
	char	**args;

	args = ft_split(data->argv[ind + 2], 32);
	if (!args)
		free_exit(args, data, 4);
	node = *lst;
	node = get_to_node(node, ind);
	fd_closer(1, lst);
	fd_outf = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: failed to open file");
		free_array(args);
		close (node->fd[0]);
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(node->fd[0], STDIN_FILENO);
	if (dup2(node->fd[0], STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
		close(fd_outf);
		fd_closer(0, lst);
		free_array(args);
		free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
	close (node->fd[0]);
	close(fd_outf);
	if (execve(data->dirs[ind], args, data->env) == -1)
		free_exit(args, data, 1);
}

t_plist	*get_to_node(t_plist *node, int ind)
{
	int	i;

	i = 0;
	while (i < ind - 1)
	{
		node = node->next;
		i++;
	}
	return (node);
}
