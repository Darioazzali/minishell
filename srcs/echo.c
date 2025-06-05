/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 echo.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/05 16:10:21 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/05 16:12:48 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	bool	skip_nl;

	av++;
	if (ac != 1)
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
			if (*(av +1))
				write(1, " ", 1);
			av++;
		}
		if (skip_nl == false)
			write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
	}
	return (0);
}
