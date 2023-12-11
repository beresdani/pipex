/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:37:28 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:07:09 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(str + i) = c;
		i++;
	}
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
    char    str1[26] = {"this is the original text"};
    char    str2[26] = {"this is the original text"};

    ft_memset(&str1[3], '&', 6);
    printf("%s\n", str1);
    memset(&str2[3], '&', 6);
    printf("%s\n", str2);
    return (0);
}
*/
