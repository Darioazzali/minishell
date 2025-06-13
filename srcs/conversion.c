/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:13:26 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/12 13:13:52 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ltos(long usec, char *res)
{
	long	temp;
	size_t	len;
	int		pos;

	temp = usec;
	len = 0;
	if (usec == 0)
		res[0] = '0';
	else if (usec < 0)
		return (-1);
	else
	{
		while (temp > 0)
		{
			len++;
			temp /= 10;
		}
		pos = len - 1;
		while (usec > 0)
		{
			res[pos--] = '0' + (usec % 10);
			usec /= 10;
		}
	}
	return (len);
}
