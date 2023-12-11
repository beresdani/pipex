/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:05:34 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:06:37 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (dest - src < 0)
	{
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
		return (dest);
	}
	else
	{
		i = n;
		while (i > 0)
		{
			*(char *)(dest + i - 1) = *(char *)(src + i - 1);
			i--;
		}
		return (dest);
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char dest1[100] = "";
	char dest2[100] = "";
	char src1[100] = "This string will be used 
	to implement the memmove() function.";
	char src2[100] = "This string will be used 
	to implement the memmove() function.";

	printf("%s\n", (char *)ft_memmove(src1 + 11, src1, 29));
	printf("%s\n", (char *)memmove(src2 + 11, src2, 29));
	printf("%s\n", (char *)ft_memmove(dest1, src1, 60));
	printf("%s\n", (char *)memmove(dest2, src2, 60));
	printf("%s\n", (char *)memmove(src2, src2 + 6, 10));
	printf("%s\n", (char *)ft_memmove(src1, src1 + 6, 10));
	
	return (0);
}
*/
