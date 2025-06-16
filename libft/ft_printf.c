/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:16:08 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:09:23 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	char		*cursor;
	int			b_printed;
	int			res;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	cursor = (char *) fmt;
	b_printed = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			res = ft_print_cursor(&cursor, &fmt, &b_printed, args);
			if (res == -1)
				return (-1);
		}
		++fmt;
	}
	res = write(1, cursor, fmt - cursor);
	if (res == -1)
		return (-1);
	va_end(args);
	return (b_printed + res);
}
