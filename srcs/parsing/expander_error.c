/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expander2.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/16 14:30:14 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/16 14:32:14 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "expander.h"

void	*expand_err_null(t_expander *expander, t_expander_error exp_err)
{
	set_expander_error(expander, exp_err);
	return (NULL);
}

int	expand_err_code(t_expander *expander, t_expander_error exp_err,
					int code)
{
	set_expander_error(expander, exp_err);
	return (code);
}

void	set_expander_error(t_expander *expander, t_expander_error exp_err)
{
	if (exp_err == EXP_ERR_MALLOC)
		expander->err = EXP_ERR_MALLOC;
	if (exp_err == EXP_ERR_OTHER)
		expander->err = EXP_ERR_OTHER;
}
