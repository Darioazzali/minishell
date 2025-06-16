/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:08:55 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:14:51 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_LEN 1024

int	check_base(char *base)
{
	int		base_len;
	int		i;

	base_len = 0;
	while (base[base_len])
	{
		i = 0;
		while (i < base_len && base[i] != base[base_len])
			i++;
		if (i != base_len || base[base_len] == '+' || base[base_len] == '-' )
			return (-1);
		base_len++;
	}
	return (base_len);
}

int	ft_putnbr_base(unsigned long long int nbr, char *base)
{
	int					base_len;
	char				res[MAX_LEN];
	int					i;
	unsigned long int	nbr_long;

	base_len = check_base(base);
	nbr_long = nbr;
	if (base_len < 2)
		return (-1);
	if (!nbr)
		return (write(1, base, 1));
	i = 0;
	while (nbr_long)
	{
		res[MAX_LEN - (i++)] = *(base + nbr_long % base_len);
		nbr_long /= base_len;
	}
	return (write(1, &res[MAX_LEN - i + 1], i));
}
