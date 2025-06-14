/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:36:37 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/14 12:37:21 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*strip_newline(char *g_line)
{
	char	*last_nl;

	last_nl = ft_strrchr(g_line, '\n');
	if (last_nl)
		*last_nl = '\0';
	return (g_line);
}
