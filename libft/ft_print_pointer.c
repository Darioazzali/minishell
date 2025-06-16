/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:36:28 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:10:12 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_print_pointer(void *ptr)
{
	uintptr_t	ptr_value;
	int			res;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	ptr_value = (uintptr_t) ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	res = ft_putnbr_base(ptr_value, "0123456789abcdef");
	if (res == -1)
		return (-1);
	return (res + 2);
}
