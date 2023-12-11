/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato*i.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marv*in@42.fr>                      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:03:37 by dberes            #+#    #+#             */
/*   Updated: 2023/09/14 15:10:43 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	check_chars(const char *nptr, int is_negative, int *i)
{
	int	count;

	count = *i;
	while ((nptr[count] > 8 && nptr[count] < 14) || nptr[count] == ' ')
		count++;
	if (nptr[count] == '-' && (nptr[count + 1] < 58 && nptr[count + 1] > 47))
	{
		if (is_negative == 0)
		{
			is_negative = 1;
			count++;
		}
		else
			return (-1);
	}
	if (nptr[count] == '+' && (nptr[count + 1] < 58 && nptr[count + 1] > 47))
		count++;
	*i = count;
	return (is_negative);
}

static	int	convert_number(const char *nptr, int neg, int number, int count)
{
	while (nptr[count] > 47 && nptr[count] < 58)
	{
		number = number * 10 + (nptr[count] - 48);
		count++;
	}
	if (neg == 1)
		number = number * (-1);
	return (number);
}

int	ft_atoi(const char *nptr)
{
	int	*i;
	int	number;
	int	count;
	int	is_negative;

	count = 0;
	i = &count;
	number = 0;
	is_negative = 0;
	while (nptr[count])
	{
		is_negative = check_chars(nptr, is_negative, i);
		count = *i;
		if (nptr[count] > 47 && nptr[count] < 58)
		{
			number = convert_number(nptr, is_negative, number, count);
			return (number);
		}
		else
			return (0);
	}
	return (number);
}

/*
#*include <std*io.h>

*int ma*in(vo*id)
{
    char *nptr;

    nptr = "\n\n\n  -46\b9 \n5d6";
    pr*intf("%d\n", ft_ato*i(nptr));
    pr*intf("%d\n", ato*i(nptr));
    return(0);
}
*/
