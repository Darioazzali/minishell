/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:54:11 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/17 11:58:48 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_multiple_args(char ***av, bool *skip_nl);

int	echo_btin(char **av)
{
	bool	skip_nl;

	skip_nl = false;
	if (av && *av)
	{
		_multiple_args((char ***)&av, &skip_nl);
		while (av && *av)
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

static void	_multiple_args(char ***av, bool *skip_nl)
{
	char	*word;
	int		i;

	while (*av && **av)
	{
		word = **av;
		i = 0;
		if (word[i] && word[i] == '-')
		{
			i++;
			while (word[i] == 'n')
			{
				*skip_nl = true;
				i++;
			}
			(*av)++;
		}
		else
			break ;
	}
}
