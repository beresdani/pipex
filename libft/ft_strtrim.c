/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:01:46 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:16:55 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	check_set(char s, const char *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen((char *)set))
	{
		if (s == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

static	char	*empty_malloc(size_t len)
{
	char	*str;

	str = (char *)malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = 0;
	return (str);
}

static	char	*make_malloc(size_t len)
{
	char	*str;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

static	char	*write_string(char const *s1, char *str, size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1)
		return (NULL);
	while (check_set(s1[i], set) != 0 && s1[i] != 0)
		i++;
	if (s1[i] == 0)
	{
		str = empty_malloc(1);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	len = ft_strlen((char *)s1);
	while (check_set(s1[len - 1], set) != 0)
		len--;
	len = len - i;
	str = make_malloc(len);
	if (str == NULL)
		return (NULL);
	str = write_string(s1, str, len, i);
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
    char *s1;
    char *set;

    s1 = " xxx awert  xxx";
    set = " x";
    printf("%s\n", ft_strtrim(s1, set));
    return (0);
}
*/
