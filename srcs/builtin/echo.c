/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:54:11 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/26 10:49:15 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_btin(char **av)
{
	bool	skip_nl;

	skip_nl = false;
	if (av && *av)
	{
		while (*av && ft_strcmp(*av, "-n") == 0)
		{
			skip_nl = true;
			av++;
		}
		while (*av)
		{
			write(1, *av, ft_strlen(*av));
			if (*(av + 1))
				write(1, " ", 1);
			av++;
		}
		if (skip_nl == false)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (0);
}
