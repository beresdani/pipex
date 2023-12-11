/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:53:37 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:11:38 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen((char *)src);
	if (size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	j = 0;
	if (dst_len >= size)
		return (size + src_len);
	while (src[j] != 0 && dst_len + j < size -1)
	{
		dst[dst_len + j] = src[j];
		j++;
	}
	dst[dst_len + j] = 0;
	return (dst_len + src_len);
}

/*
#include <stdio.h>

int	main(void)
{
	char	dst1[] = "space";
	char	dst2[] = "space";
	char	*src1;
	char	*src2;
	int		r1;
	int		r2;

	src1 = "is left";
	src2 = "is left";
	r2 = strlcat(NULL, src2, 0);
	printf("dest %s\n length %d\n", dst2, r2);
	r1 = ft_strlcat(dst1, src1, 5);
	printf("dest %s\n length %d\n", dst1, r1);
	return (0);
}
*/
