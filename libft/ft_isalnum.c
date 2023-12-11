/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:25:18 by dberes            #+#    #+#             */
/*   Updated: 2023/09/05 11:43:36 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int a)
{
	if (a < 91 && a > 64)
		return (1);
	else if (a < 123 && a > 96)
		return (2);
	else if (a > 47 && a < 58)
		return (3);
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%d\n", ft_isalnum(67));
	printf("%d\n", isalnum(67));
	printf("%d\n", ft_isalnum(98));
	printf("%d\n", isalnum(98));
	printf("%d\n", ft_isalnum(57));
	printf("%d\n", isalnum(57));
	printf("%d\n", ft_isalnum(8));
	printf("%d\n", isalnum(8));

	return (0);
}
*/
