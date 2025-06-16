/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:21:28 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/15 19:27:54 by aluque-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	bool	skip_nl;

	av++;
	if (1 != ac)
	{
		if (ft_strcmp(*av, "-n", 2) == 0)
		{
			skip_nl = true;
			av++;
		}
		else
			skip_nl = false;
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
