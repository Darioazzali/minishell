/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:44 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/17 07:37:43 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*__ft_next_line(char *buf)
{
	char	*next_line;
	char	*eol;
	int		len;

	eol = ft_strchr(buf, '\n');
	if (!eol)
		eol = ft_strchr(buf, '\0') - 1;
	len = (eol - buf) + 1;
	next_line = ft_substr(buf, 0, len);
	if (!next_line)
		return (NULL);
	return (next_line);
}
