/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:08 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:18:16 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c < 91 && c > 64)
		c = c + 32;
	return (c);
}

/*
#include <stdio.h>

int main(void)
{
    char    c;

    c = 'R';
    printf("%c\n", ft_tolower(c));
    printf("%c\n", tolower(c));
    return (0);
}
*/
