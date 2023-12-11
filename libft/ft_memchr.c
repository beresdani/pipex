/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:07:15 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:05:11 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int main(void)
{
    unsigned char c;
    const void *s;

    s = "|\x12\xff\x09\x42\2002\42|\\";
    printf("%ld %s\n", (ft_memchr(s, '\200', 10) - s), 
	(char *)ft_memchr(s, '\200', 10));
	printf("%ld %s\n", (memchr(s, '\200', 10) - s), 
	(char *)memchr(s, '\200', 10));
	return(0);	
}
*/
