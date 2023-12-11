/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:01:54 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:15:50 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*check_little(const char *b, const char *t, size_t l, size_t i)
{
	size_t	j;

	if (b[i] == t[0])
	{
		j = 0;
		while (t[j] != 0 && (i + j) < l)
		{
			if (t[j] == b[i + j])
				j++;
			else
				break ;
		}
		if (t[j] == 0)
			return ((char *)&b[i]);
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	if (big[0] == 0 && (int)len < 0)
		return (NULL);
	while (i < len)
	{
		if (check_little(big, little, len, i) != 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int   main(void)
{
    const char *big;
    const char *little;

    big= "lets find this in this";
    little = "th";
	if (ft_strnstr(big, little, 4) == NULL)
		printf("NULL\n");
    else
		printf("%s\n", ft_strnstr(big, little, 4));
	if (strnstr(big, little, 4) == NULL)
		printf("NULL\n");
	else
		printf("%s\n", strnstr(big, little, 4));
}
*/
