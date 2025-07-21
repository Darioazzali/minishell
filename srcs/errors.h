/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 07:01:38 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/21 07:02:03 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

void			print_program_error(char *program_name, char *message);
int				print_shell_error_ret_int(char *message, int errcode);
void			print_error(char *message);
void			print_shell_error(char *message);
void			*print_shell_error_ret_null(char *message);
#endif
