/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:01:05 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:11:00 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	char	*write_string(char *s1, char *s2, size_t len1, size_t len2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc((len1 + len2 + 1) * 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!s1)
		return (NULL);
	str = write_string((char *)s1, (char *)s2, len1, len2);
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
    char    *s1;
    char    *s2;

    s1 = "to this part ";
    s2 = "we are adding this";
    printf("%s\n", ft_strjoin(s1, s2));
    return (0);
}
*/
