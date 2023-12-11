/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:26:40 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:12:09 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (src[i] != 0)
		i++;
	len = i;
	if (size == 0)
		return (len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = 0;
	return (len);
}

/*
#include <stdio.h>

int	main(void)
{
	char	dst1[20];
	char	dst2[20];
	char	*src1;
	char	*src2;
	int		r1;
	int		r2;

	src1 = "BBBB";
	src2 = "BBBB";
	memset(dst1, 'A', 20);
	memset(dst2, 'A', 20);
	printf("%s\n", dst1);
	printf("%s\n", dst2);
	r1 = ft_strlcpy(dst1, src1, sizeof(dst1));
	r2 = strlcpy(dst2, src2, sizeof(dst2));
	
	printf("%s\n", dst1);
	printf("%s\n", dst2);
	printf("copied '%s' into '%s', length %d\n", src1, dst1, r1);
	printf("copied '%s' into '%s', length %d\n", src2, dst2, r2);
	return (0);
}
*/
