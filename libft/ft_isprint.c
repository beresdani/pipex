/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:47:48 by dberes            #+#    #+#             */
/*   Updated: 2023/09/04 16:51:15 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int a)
{
	if (a < 127 && a > 31)
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%d\n", ft_isprint(6));
	printf("%d\n", isprint(6));
	printf("%d\n", ft_isprint(45));
	printf("%d\n", ft_isprint(45));
	return (0);
}
*/
