/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:37:23 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:10:02 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int nbr, bool upper)
{
	char	*base_lower;
	char	*base_upper;

	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	if (upper)
	{
		return (ft_putnbr_base(nbr, base_upper));
	}
	return (ft_putnbr_base(nbr, base_lower));
}
