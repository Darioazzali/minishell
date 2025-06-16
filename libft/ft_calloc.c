/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:44:30 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/27 15:44:37 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

static bool	is_overflow(size_t nmemb, size_t size)
{
	size_t	total_bytes;

	total_bytes = nmemb * size;
	if (total_bytes < nmemb || total_bytes < size)
		return (true);
	return (false);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_bytes;

	total_bytes = nmemb * size;
	if (total_bytes >= PTRDIFF_MAX)
		return (NULL);
	if (!total_bytes)
		return (malloc(0));
	if (is_overflow(nmemb, size))
		return (NULL);
	ptr = malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
