/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/31 15:56:23 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *haystack, int needle)
{
	int				len;
	const char		*end;

	len = ft_strlen(haystack);
	end = haystack + len;
	while (end >= haystack)
	{
		if (*end == (unsigned char) needle)
			return ((char *) end);
		end--;
	}
	return ((char *)0);
}
