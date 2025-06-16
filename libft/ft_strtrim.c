/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:39:18 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 15:39:23 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*start;
	char	*end;
	char	*res;

	if (!*set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	start = (char *) s1;
	while (*start && ft_strchr(set, *start))
		start++;
	if (!*start)
		return (ft_strdup(""));
	end = (char *) s1 + len - 1;
	while (*end && ft_strchr(set, *end))
		end--;
	res = ft_substr(s1, start - s1, end - start + 1);
	return (res);
}
