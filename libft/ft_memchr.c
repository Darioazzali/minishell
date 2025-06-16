/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:45:23 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 19:08:33 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	c = (unsigned char) c;
	ptr = (unsigned char *)s;
	while (n)
	{
		if (*ptr == c)
			return ((void *) ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
