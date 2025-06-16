/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:44:08 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/14 11:09:51 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_cursor(char **cursor, const char **fmt, int *b_pr, va_list args)
{
	int	res;

	write(1, *cursor, (*fmt - *cursor));
	*b_pr += (*fmt)++ - *cursor;
	res = print_formatted_argument(args, **fmt);
	if (res == -1)
		return (-1);
	*b_pr += res;
	*cursor = (char *)*fmt + 1;
	return (res);
}

int	print_formatted_argument(va_list args, char fmt)
{
	if (fmt == 'd' || fmt == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (fmt == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (fmt == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (fmt == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (fmt == 'p')
		return (ft_print_pointer(va_arg(args, char *)));
	else if (fmt == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), false));
	else if (fmt == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), true));
	else if (fmt == '%')
		return (ft_print_char('%'));
	return (-1);
}

int	ft_print_str(char *s)
{
	size_t	len;
	int		w_res;

	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	w_res = write(1, s, len);
	if ((w_res) != (int) len)
		return (-1);
	return (len);
}

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_int(int i)
{
	int		b_written;
	char	*res;

	res = ft_itoa(i);
	if (res == NULL)
		return (-1);
	b_written = ft_print_str(res);
	free(res);
	return (b_written);
}
