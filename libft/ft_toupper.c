/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:00:58 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:18:26 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c = c - 32;
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	char	c;

	c = 'f';
	printf("%c\n", ft_toupper(c));
	printf("%c\n", toupper(c));
	return (0);
}
*/
