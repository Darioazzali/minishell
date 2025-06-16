/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:27:17 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/23 18:51:50 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>

static	size_t	ft_digit_n(int n)
{
	size_t	digits;

	digits = 1;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		digits++;
		if (n == INT_MIN)
		{
			digits++;
			n /= 10;
		}
		n = -n;
	}
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*res;
	char	*ptr;

	res = (char *) malloc(sizeof(char) * ft_digit_n(n));
	if (!res)
		return (NULL);
	if (n < 0)
		*res = '-';
	ptr = res + ft_digit_n(n) - 1;
	*ptr-- = '\0';
	if (n == INT_MIN)
	{
		*ptr-- = - (n % 10) + '0';
		n = n / 10;
	}
	if (n < 0)
		n = -n;
	while (n / 10)
	{
		*ptr-- = (n % 10) + '0';
		n /= 10;
	}
	*ptr = (n % 10) + '0';
	return (res);
}
