/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:47:23 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 18:02:05 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *) malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}
