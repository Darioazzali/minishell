/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:21:28 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/13 14:21:30 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	bool	skip_nl;

	av++;
	if (1 != ac)
	{
		if (strcmp(*av, "-n") == 0)
		{
			skip_nl = true;
			av++;
		}
		else
			skip_nl = false;
		while (*av)
		{
			write(1, *av, strlen(*av));
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
