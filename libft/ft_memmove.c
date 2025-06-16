/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:25:05 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/31 16:14:48 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, unsigned int n)
{
	char			*dst_ptr;
	unsigned int	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	dst_ptr = (char *)dst;
	if (dst_ptr > (char *) src)
	{
		while (n)
		{
			*(dst_ptr + n -1) = *((char *) src + n - 1);
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			*(dst_ptr + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}
