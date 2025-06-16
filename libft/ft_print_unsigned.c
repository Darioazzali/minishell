/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:06:24 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:10:22 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX_UINT_BUF 50

int	ft_print_unsigned(unsigned int n)
{
	char	res[MAX_UINT_BUF];
	size_t	i;

	if (n == 0)
		return (write(1, "0", 1));
	i = 0;
	while (n / 10)
	{
		res[MAX_UINT_BUF - i++ - 1] = '0' + (n % 10);
		n /= 10;
	}
	res[MAX_UINT_BUF - i - 1] = '0' + (n % 10);
	return (write(1, &res[MAX_UINT_BUF - i - 1], i + 1));
}
