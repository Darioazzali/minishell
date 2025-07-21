/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:13:26 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/21 06:54:12 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ltos(long nbr, char *res)
{
	long	temp;
	size_t	len;
	int		pos;

	temp = nbr;
	len = 0;
	if (nbr == 0)
		res[0] = '0';
	else if (nbr < 0)
		return (-1);
	else
	{
		while (temp > 0)
		{
			len++;
			temp /= 10;
		}
		pos = len - 1;
		while (nbr > 0)
		{
			res[pos--] = '0' + (nbr % 10);
			nbr /= 10;
		}
	}
	return (len);
}
