/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:06:22 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:05:21 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) < *(unsigned char *)(s2 + i))
			return (-1);
		else if (*(unsigned char *)(s1 + i) > *(unsigned char *)(s2 + i))
			return (1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
    const void *s1;
    const void *s2;

    s1 = "atoms\0abc";
    s2 = "atoms\0abc";
    printf("%d\n", ft_memcmp(s1, s2, 8));
    printf("%d\n", memcmp(s1, s2, 8));
    return (0);
}
*/
