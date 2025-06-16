/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:39:43 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 15:39:44 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (start + len >= s_len)
		len = s_len - start;
	res = (char *) ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, (s + start), len + 1);
	return (res);
}
