/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:15:47 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/19 11:37:09 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DEBUG_H
# define DEBUG_H

# include "libft.h"

/* ANSI Color Codes */
# define RESET		"\033[0m"
# define BOLD		"\033[1m"

/* Colors */
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

/* Combined formatting for debug output */
# define LABEL_START	"\033[1m\033[36m"		/* Bold cyan */
# define VALUE_START	"\033[32m"				/* Green */
# define TYPE_START		"\033[33m"				/* Yellow */

/* Pre-built format strings */
# define TOKEN_VALUE_LABEL	"\033[1m\033[36mtoken_value\033[0m: \033[32m"
# define TOKEN_TYPE_LABEL	"\033[1m\033[36mtoken_type\033[0m:  \033[33m"

typedef struct s_buffer_ctx
{
	char	*ptr;
	char	*start;
	int		remaining;
	int		total_len;
}	t_buffer_ctx;

t_buffer_ctx	init_buffer_ctx(char *buffer, char *ptr, int total_len);
void			append_to_buffer(t_buffer_ctx *ctx, const char *str);
#endif
