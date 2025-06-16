/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:45:51 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 18:53:27 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	len;

	len = ft_strlen((char *) src);
	if (size == 0)
		return (len);
	while (*src && size > 1)
	{
		*dst++ = *src++;
		size --;
	}
	*dst = '\0';
	return (len);
}
