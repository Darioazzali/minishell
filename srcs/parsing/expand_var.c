/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:47:03 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/01 17:03:54 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*handle_shell_parameter(t_expander *expander);
static int	should_be_literal_dollar(char c);
static char	*extract_variable_name(t_expander *expander);
static char	*get_variable_value(t_expander *expander, char *var_name);

char	*expand_shell_param(t_expander *expander)
{
	char	*ret;
	char	*var_name;

	expander->start = ++expander->cursor;
	ret = NULL;
	if (should_be_literal_dollar(*expander->cursor))
		return (ft_strdup("$"));
	if (*expander->cursor == '$' || *expander->cursor == '?'
		|| ft_isdigit(*expander->cursor))
		return (handle_shell_parameter(expander));
	var_name = extract_variable_name(expander);
	if (!var_name)
		return (NULL);
	ret = get_variable_value(expander, var_name);
	if (!ret)
		return (ft_strdup(""));
	return (ret);
}

static char	*get_variable_value(t_expander *expander, char *var_name)
{
	char	*val;
	char	*ret;

	val = get_shell_var_value(expander->envs, var_name);
	ret = NULL;
	if (val)
		ret = ft_strdup(val);
	free(var_name);
	return (ret);
}

/** @brief Extract variable name from token
* At the same time the cursor is advanced till
* the end of the variable name.
*/
static char	*extract_variable_name(t_expander *expander)
{
	char	*name;

	while (*expander->cursor && (ft_isdigit(*expander->cursor)
			|| ft_isalpha(*expander->cursor) || *expander->cursor == '_'))
		expander->cursor++;
	name = ft_substr(expander->token,
			expander->start - expander->token,
			expander->cursor - expander->start);
	if (!name)
		expand_err_null(expander, EXP_ERR_MALLOC);
	return (name);
}

static char	*handle_shell_parameter(t_expander *expander)
{
	char	*ret;

	if (*expander->cursor == '$')
		ret = ft_itoa(expander->ctx->pid);
	else if (*expander->cursor == '?')
		ret = ft_itoa(expander->ctx->exit_status);
	else if (*expander->cursor == '0')
		ret = (ft_strdup("minishell"));
	else if (ft_isdigit(*expander->cursor))
		ret = (ft_strdup(""));
	else
		return (ft_strdup("$"));
	expander->cursor++;
	return (ret);
}

static int	should_be_literal_dollar(char c)
{
	return (c == '\0' || c == '"' || c == '\'' || c == ' '
		|| c == '\t' || c == '\n' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')' || c == '<'
		|| c == '>' || c == '`');
}
