/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:26:49 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/02 07:44:16 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "parser.h"

typedef enum e_expander_error
{
	EXP_NO_ERROR,
	EXP_ERR_MALLOC,
	EXP_ERR_OTHER
}	t_expander_error;

/** Data structure that holds the state of the 
 * variable expansion phase.
 * @note The token should not be freed
 * @note The only memory allocated is the expanded field
 * */
typedef struct s_expander
{
	const char			*token;		///< A pointer to the original token
	char				*cursor;	///< A pointer to the current char
	char				*start;		///< A pointer to the start of the token
	char				*expanded;	///< The result of expansion
	t_parser_mode		mode;		///< Single quote, double quote or normal
	t_expander_error	err;		///< The error code
	t_envs				*envs;		///< The environment
	t_ctx				*ctx;		///< The context
}	t_expander;

/**
 * @brief Sets the expander error code and returns NULL
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 * @note The error code is set from the enum `t_expander_error`
*/
void		*expand_err_null(t_expander *expander, t_expander_error exp_err);

/**
 * @brief Sets the expander error code and returns the error code
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 * @param code The error code
 *
 * @note The error code is set from the enum `t_expander_error`
*/
int			expand_err_code(t_expander *expander, t_expander_error exp_err,
				int code);

/* @brief Append shell parameter to the expanded token
 * Expand the shell variable/parameter name pointed by the cursor
 * and append it to the string.
 * The cursor is advanced to the end of the shell variable/parameter name.
 * */
void		append_shell_variable(t_expander *expander);

/** @brief 	Process a character of the string.
 *			
 *			The expander proceed char by char to process the token.
 *			In order to expand the variable, the expander keeps track
 *			of the quote mode.
 *			When a variable/parameter is found, the expander replace
 *			the variable name with its value.
 *
 * */
void		exp_process_char(t_expander *expander);

/**
 * @brief Sets the expander error code
 *
 * @param expander The expander to set the error on
 * @param exp_err The error to set
 *
 * @note The error code is set from the enum `t_expander_error`
*/
void		set_expander_error(t_expander *expander, t_expander_error exp_err);

/** @brief Initialize the expander
 *
 * The expander is meant to be used to expand the variables
 * in a single token.
 *
 * The only memory allocated to be freed is the expander->expanded field
 * that contains the expanded token.
 *
 * @param expander A pointer to memory that holds the address of the expander
 * 				   to initialize.
 * @param ctx The context to use
 * @param token A pointer to the original token.
 *
 * @note The token should not be freed.
 * */
int			init_expander(t_expander *expander,
				t_ctx *ctx,
				const char *const token);

/** @brief 	Join the character until the cursor to the partially expanded token.
 *			
 *			The expander keeps tracks of two pointers:
 *			1. start: The pointer to the last char joined
 *			2. cursor: The pointer to the current char
 *
 *			When the expander encounter a shell variable or parameter,
 *			it should join the substring from the last char joined
 *			to the actual character before the shell variable/parameter.
 *
 *			@note This function allocates memory and can fail.
 *			If it does it sets the expander code.
 *
 *			@return 0 on success
 * */
int			join_until_cursor(t_expander *expander);

/** @brief Clean the expander and print the error */
void		*clean_expander(t_expander *expander);

char		*expand_shell_param(t_expander *expander);
#endif
