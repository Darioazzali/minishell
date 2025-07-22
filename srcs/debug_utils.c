/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:24:23 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/22 10:56:29 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"

/** @brief Log the strcuture for debug purposes
 *
 * Prints the structure using fmt as formtting function
 * The function is responsable to free the formatted string
 *
 *	@param str the structure to log
 *	@param fmt the function to format the structure
 *
 *	@note The function frees the formatted string
 *
 * */
void	log_debug_struct(void *str, char *(*fmt) (void *))
{
	char	*fmt_str;

	fmt_str = fmt(str);
	log_debug(fmt_str);
	free(fmt_str);
}
