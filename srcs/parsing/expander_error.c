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

/**
 * @brief Sets the expander error code and returns NULL
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 * @note The error code is set from the enum `t_expander_error`
*/
void	*expand_err_null(t_expander *expander, t_expander_error exp_err)
{
	set_expander_error(expander, exp_err);
	return (NULL);
}

/**
 * @brief Sets the expander error code and returns the error code
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 * @param code The error code
 *
 * @note The error code is set from the enum `t_expander_error`
*/
int	expand_err_code(t_expander *expander, t_expander_error exp_err,
					int code)
{
	set_expander_error(expander, exp_err);
	return (code);
}

/**
 * @brief Sets the expander error code
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 *
 * @note The error code is set from the enum `t_expander_error`
*/
void	set_expander_error(t_expander *expander, t_expander_error exp_err)
{
	if (exp_err == EXP_ERR_MALLOC)
		expander->err = EXP_ERR_MALLOC;
	if (exp_err == EXP_ERR_OTHER)
		expander->err = EXP_ERR_OTHER;
}
