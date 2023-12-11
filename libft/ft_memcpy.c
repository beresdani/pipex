/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:44:07 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:05:54 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	char	dest1[50];
	char	dest2[50];
	char	*src;

	src = "letscopystuff";
	str1 = ft_memcpy(((void *)0), ((void *)0), 3);
	str2 = memcpy(((void *)0), ((void *)0), 3);

	printf("%s\n", str1);
	printf("%s\n", str2);
	return (0);
}
*/
