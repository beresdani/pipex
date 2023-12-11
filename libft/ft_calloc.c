/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:58:21 by dberes            #+#    #+#             */
/*   Updated: 2023/09/18 11:45:39 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	spaces;
	int		*array;

	spaces = nmemb * size;
	if (spaces > INT_MAX)
		return (NULL);
	array = malloc(spaces);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, spaces);
	return (array);
}

/*
#include <stdio.h>
int main(void)
{
    int	 *array1;
    int	 *array2;

	array2 = (int *)calloc(10, 8);
	printf("%n\n", array2);
    array1 = (int *)ft_calloc(10, 8);
    printf("%n\n", array1);
    
    free(array1);
    free(array2);
    return (0);
}
*/
