/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:11:16 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:09:01 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		else
			i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	char 	*s;
	char	c;

	s = "lets find the firts s";
	c = 'n';
	
	printf("%ld %s\n", (ft_strchr(s, c) - s), ft_strchr(s, c));
	printf("%ld %s\n", strchr(s, c) - s, strchr(s, c));
	return(0);	
}
*/
