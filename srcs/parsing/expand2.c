/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:24:37 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/01 17:03:44 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	handle_normal_char(t_expander *expander);
static void	handle_double_quote_char(t_expander *expander);
static void	handle_quotes(t_expander *expander);
static void	handle_escape(t_expander *expander);

/** @brief Process a character of the string.*/
void	exp_process_char(t_expander *expander)
{
	if (expander->mode == LEXI_S_QUOTE)
	{
		if (*expander->cursor == '\'')
			expander->mode = LEXI_NORMAL;
		expander->cursor++;
		return ;
	}
	if (expander->mode == LEXI_D_QUOTE)
		return (handle_double_quote_char(expander));
	return (handle_normal_char(expander));
}

/**@brief Process the characters in the expander in normal mode */
static void	handle_normal_char(t_expander *expander)
{
	if (*expander->cursor == '\'' || *expander->cursor == '"')
		return (handle_quotes(expander));
	if (*expander->cursor == '\\' && *(expander->cursor + 1))
		return (handle_escape(expander));
	if (*expander->cursor == '$')
		return (append_shell_variable(expander));
	expander->cursor++;
}

static void	handle_double_quote_char(t_expander *expander)
{
	if (*expander->cursor == '"')
	{
		expander->mode = LEXI_NORMAL;
		expander->cursor++;
		return ;
	}
	if (*expander->cursor == '\\'
		&& (
			*(expander->cursor + 1) == '$'
			|| *(expander->cursor + 1) == '"'
			|| *(expander->cursor + 1) == '\\'
		))
		return (handle_escape(expander));
	if (*expander->cursor == '$')
		return (append_shell_variable(expander));
	expander->cursor++;
}

/** @brief Handle the quotes character in normal mode
 * When one of the quotes character is encountered 
 * the expander should switch to the corresponding mode
 * and advance the cursor.
 * */
static void	handle_quotes(t_expander *expander)
{
	if (*expander->cursor == '\'')
		expander->mode = LEXI_S_QUOTE;
	else if (*expander->cursor == '"')
		expander->mode = LEXI_D_QUOTE;
	expander->cursor++;
}

/** @brief Handle the escape character. 
 * When an escape character is encountered followed by a character,
 * the expander should join the the expanded string with the new substring
 * obtained by extracting from the precedent pointer till
 * the escape character (not included).
 * Then it should set the expander->start to the next character
 * after the escape character and the cursor to the character following it
 *
 * @param expander The expander
 * */
static void	handle_escape(t_expander *expander)
{
	if (join_until_cursor(expander) == -1)
	{
		expander->err = EXP_ERR_MALLOC;
		return ;
	}
	expander->cursor++;
	expander->start = expander->cursor;
	expander->cursor++;
}
