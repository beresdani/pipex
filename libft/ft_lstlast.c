/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:43:36 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 10:44:39 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (lst == NULL)
		return (lst);
	ptr = lst;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}
