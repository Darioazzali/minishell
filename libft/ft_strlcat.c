/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:45:38 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 18:02:23 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*
 * rem_bytes-- are the remaining bytes after traversing dst.
 * the first times variable is used is only as a counter
 * so it has no meanings.
 * occup_bytes is the bytes already occupied by dst.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*original_dst;
	const char	*original_src;
	size_t		rem_bytes;
	size_t		occup_bytes;

	original_dst = dst;
	rem_bytes = size;
	while (*dst && rem_bytes-- != 0)
		dst++;
	occup_bytes = dst - original_dst;
	rem_bytes = size - occup_bytes;
	if (rem_bytes-- == 0)
		return (ft_strlen(src) + occup_bytes);
	original_src = src;
	while (*src)
	{
		if (rem_bytes != 0)
		{
			*dst++ = *src;
			rem_bytes--;
		}
		src++;
	}
	*dst = '\0';
	return (occup_bytes + src - original_src);
}
