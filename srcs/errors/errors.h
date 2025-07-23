/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 07:01:38 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/28 11:26:40 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

void			print_program_error(char *program_name, char *message);
int				print_shell_error_ret_int(char *message, int errcode);
void			print_error(char *message);
void			print_shell_error(char *message);
void			*print_shell_error_ret_null(char *message);
int				errno_to_shell_exit(int err);
void			print_exec_err(int _errno, char *prog_name);
void			err_command_not_found(char *prog_name);
#endif
