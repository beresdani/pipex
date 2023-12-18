/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:36 by dberes            #+#    #+#             */
/*   Updated: 2023/12/18 16:13:10 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	list_size(t_data **lst)
{
	int		count;
	t_data	*ptr;

	count = 0;
	ptr = *lst;
	if (lst == NULL)
		return (0);
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

t_data	*list_last(t_data **lst)
{
	t_data	*ptr;

	if (lst == NULL)
		return (*lst);
	ptr = *lst;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}

void	add_pipe_node(t_data **lst, t_data *new)
{
	t_data	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = list_last(lst);
	ptr->next = new;
}
