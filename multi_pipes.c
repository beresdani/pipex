/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:50 by dberes            #+#    #+#             */
/*   Updated: 2024/01/03 00:02:48 by dberes           ###   ########.fr       */
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
