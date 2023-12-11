/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:18:15 by dberes            #+#    #+#             */
/*   Updated: 2023/09/04 16:24:02 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 91 && c > 64) || (c < 123 && c > 96))
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("%d\n", ft_isalpha(5));
	printf("%d\n", isalpha(5));
	printf("%d\n", ft_isalpha(122));
	printf("%d\n", isalpha(122));


	return (0);
}
*/
