/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:26:49 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/01 17:02:28 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "parser.h"

typedef struct s_expander
{
	const char			*token;
	char				*cursor;
	char				*start;
	char				*expanded;	
	t_parser_mode		mode;
	t_expander_error	err;
	t_envs				*envs;
	t_ctx				*ctx;
}	t_expander;

// int		append_shell_variable(t_expander *expander);
void	append_shell_variable(t_expander *expander);
void	exp_process_char(t_expander *expander);
void	set_expander_error(t_expander *expander, t_expander_error exp_err);
#endif
