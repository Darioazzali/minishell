/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:02:26 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/28 11:26:07 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	errno_to_shell_exit(int err)
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == ENOEXEC)
		return (126);
	return (err);
}

void	print_exec_err(int _errno, char *prog_name)
{
	write(2, "minishell: ", 11);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": ", 2);
	write(2, strerror(_errno), ft_strlen(strerror(_errno)));
	write(2, "\n", 1);
}

void	err_command_not_found(char *prog_name)
{
	write(2, "minishell: ", 11);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": command not found\n", 20);
}
