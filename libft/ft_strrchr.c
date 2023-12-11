/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:42:35 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:16:21 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i] != 0)
	{
		if (s[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	else if (j == -1)
		return (NULL);
	else
		return ((char *)&s[j]);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s;
	char	c;

	s = "ksrrtthheewstzs";
	c = '\0';

	printf("%ld %s\n", (ft_strrchr(s, c) - s), ft_strrchr(s, c));
    printf("%ld %s\n", strrchr(s, c) - s, strrchr(s, c));
    return(0); 	
}
*/
