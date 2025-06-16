/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/30 18:35:58 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *haystack, int needle)
{
	while (*haystack != (unsigned char) needle)
	{
		if (*haystack == '\0')
			return ((char *) 0);
		haystack++;
	}
	return ((char *)haystack);
}
