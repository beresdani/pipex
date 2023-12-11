/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:00:38 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:09:42 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	while (s[i] != 0)
		i++;
	len = i;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

/*
#include <stdio.h>
int main(void)
{
    char *s;
    char *dup1;
    char *dup2;

    s = "duplicate me";
    dup1 = ft_strdup(s);
    dup2 = strdup(s);
    printf("%s\n", dup1); 
    printf("%s\n", dup2);
    free(dup1);
    free(dup2);
    return (0);
}
*/
