/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:17 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/10 16:25:29 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/** @brief Print a program error message.
 *
 * Prints the program name followed by a colon, a space, and the error message
 * to the standard error stream.
 * If no error message is provided, the default error message "Error" is used.
 *
 * @param program_name The name of the program.
 * @param message The error message.
 */
void	print_program_error(char *program_name, char *message);
#endif
