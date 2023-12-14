/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:59:12 by dberes            #+#    #+#             */
/*   Updated: 2023/12/14 14:27:32 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	size_t	check_number(char const *s, char c)
{
	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	if (s[0] == 0)
		return (0);
	if (c == 0)
		return (1);
	while (s[i] != 0)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (!s[i])
			return (0);
		num++;
		while (s[i] != c && s[i] != 0)
			i++;
		while (s[i] == c)
			i++;
	}
	return (num);
}

static	size_t	check_word_length(char const *s, int c, size_t *start)
{
	size_t	i;

	i = *start;
	while (s[i] == c)
		i++;
	*start = i;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i - *start);
}

static	char	**check_malloc(char **array, size_t k)
{
	size_t	i;

	i = 0;
	if (array[k] == NULL)
	{
		while (i < k)
		{
			free (array[i]);
			i++;
		}
		free (array);
		return (NULL);
	}
	return (array);
}

static	char	**words_malloc(char **array, char const *s, char c, size_t num)
{
	size_t	k;
	size_t	*start;
	size_t	len;
	size_t	count;

	k = 0;
	count = 0;
	start = &count;
	while (k < num)
	{
		len = check_word_length(s, c, start);
		array[k] = (char *)malloc((len + 1) * sizeof(char));
		if (check_malloc(array, k) == 0)
			return (NULL);
		array[k][len] = 0;
		count += len;
		while (s[count] == c && c != 0)
			count++;
		k++;
	}
	array[k] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**array;

	i = 0;
	k = 0;
	array = (char **)malloc((check_number(s, c) + 1) * sizeof(char *));
	if (array == NULL || !s)
		return (NULL);
	array = words_malloc(array, s, c, check_number(s, c));
	if (array == NULL)
		return (NULL);
	while (k < check_number(s, c))
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i] != 0)
			array[k][j++] = s[i++];
		k++;
	}
	return (array);
}

/*
#include <stdio.h>

int main(void)
{
	int			i;
	char		**array;

	i = 0;
	array = ft_split("\0aabbb", '\0');
	if (array == NULL)
	{
		printf("%s\n", "NULL");
		return (0);
	}
	while (i < 1)
	{	
   		printf("%s\n", array[i]);
		i++;
	}
    return (0);
}
*/
