/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:02:16 by dberes            #+#    #+#             */
/*   Updated: 2023/09/14 14:26:54 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	char	*check_start(void)
{
	char	*sub;

	sub = (char *)malloc(1 * sizeof(char));
	if (sub == NULL)
		return (NULL);
	sub[0] = 0;
	return (sub);
}

static	char	*check_len(char const *s, unsigned int start)
{
	size_t	i;
	char	*sub;

	i = 0;
	sub = (char *)malloc(((ft_strlen((char *)s) - start + 1) * sizeof(char)));
	if (sub == NULL)
		return (NULL);
	while (s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

static	char	*write_string(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		sub = check_start();
		return (sub);
	}
	if (len >= (ft_strlen((char *)s) - start))
	{
		sub = check_len(s, start);
		return (sub);
	}
	sub = write_string(s, start, len);
	return (sub);
}

/*
#include <stdio.h>

int main(void)
{
    char *s1;
    char *s2;

    s1 = "take a part of this";
    printf("%s\n", ft_substr("tripouille", 1, 1));
    return (0);
}
*/
