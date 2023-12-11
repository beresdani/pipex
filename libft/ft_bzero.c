/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:49:14 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:02:35 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(str + i) = '\0';
		i++;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char	str1[30] = "lets put in some zeros";
	char	str2[30] = "lets put in some zeros";

	ft_bzero(&str1[5], 4);
	printf("%s\n", str1);
	bzero(&str2[5], 4);
	printf("%s\n", str2);
	return (0);
}
*/
