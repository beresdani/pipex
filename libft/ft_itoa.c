/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:34:15 by dberes            #+#    #+#             */
/*   Updated: 2023/09/14 11:32:16 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	check_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static	int	check_size(int n)
{
	int	i;
	int	q;

	i = 1;
	q = n;
	while (q > 9 || q < -9)
	{
		q = q / 10;
		i++;
	}
	if (check_negative(n) == 1)
		i++;
	return (i);
}

static	char	*make_string(char *str, int n)
{
	int		i;
	int		q;
	char	digit;

	q = check_size(n);
	if (check_negative(n) == 1)
	{
		n = n * (-1);
		str[0] = '-';
	}
	i = 0;
	while (i < q)
	{
		digit = n % 10 + 48;
		n = n / 10;
		if (str[q - i - 1] != '-')
			str[q - i - 1] = digit;
		i++;
	}
	str[q] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	int		q;
	int		int_min;
	char	*str;

	int_min = 0;
	if (n == -2147483648)
	{
		n = n + 1;
		int_min = 1;
	}
	q = check_size(n);
	str = (char *)malloc((q + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	make_string(str, n);
	if (int_min == 1)
		str[10] = '8';
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	int	n;

	n = -24564314;
	printf("%s\n", ft_itoa(n));
	return (0);
}
*/
