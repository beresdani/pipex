/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:51:35 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 10:52:39 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*ptr;

	ptr = lst;
	lst = lst->next;
	if (ptr == NULL)
	{
		free(ptr);
		return ;
	}
	del(ptr->content);
	free(ptr);
}
