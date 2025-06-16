/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:44:10 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 18:02:40 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	if (!n)
		return (0);
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*c1 && *c2 && *c1 == *c2 && n > 1)
	{
		c1++;
		c2++;
		n--;
	}
	return (*c1 - *c2);
}
