/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expander.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 06:35:50 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/14 06:38:52 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static char	*handle_shell_parameter(t_expander *expander);

int	init_expander(t_expander *expander, t_ctx *ctx, const char *token)
{
	expander->token = token;
	expander->cursor = (char *)token;
	expander->start = expander->cursor;
	expander->expanded = ft_strdup("");
	expander->envs = ctx->envs;
	if (!expander->expanded)
		return (-1);
	expander->err = EXP_NO_ERROR;
	expander->ctx = ctx;
	return (0);
}

int	join_until_cursor(t_expander *expander)
{
	char	*tmp;
	char	*prev;
	int		start_idx;
	int		end_idx;

	start_idx = expander->start - expander->token;
	end_idx = expander->cursor - expander->start;
	prev = ft_substr(expander->token, start_idx, end_idx);
	if (!prev)
		return (expand_err_code(expander, EXP_ERR_MALLOC, -1));
	tmp = ft_strjoin(expander->expanded, prev);
	free(prev);
	if (!tmp)
		return (expand_err_code(expander, EXP_ERR_MALLOC, -1));
	free(expander->expanded);
	expander->expanded = tmp;
	return (0);
}

char	*expand_shell_param(t_expander *expander)
{
	char	*ret;
	char	*tmp;

	expander->cursor++;
	expander->start = expander->cursor;
	if (*expander->cursor == '$' || *expander->cursor == '?'
		|| *(expander->cursor + 1) == '\0' || ft_isdigit(*expander->cursor))
		ret = handle_shell_parameter(expander);
	else
	{
		while (*expander->cursor && (ft_isdigit(*expander->cursor)
				|| ft_isalpha(*expander->cursor)))
			expander->cursor++;
		tmp = ft_substr(expander->start, 0, expander->cursor - expander->start);
		if (!tmp)
			expand_err_null(expander, EXP_ERR_MALLOC);
		ret = ft_strdup(get_shell_var_value(expander->envs, tmp));
		free(tmp);
	}
	if (!ret)
		return (ft_strdup(""));
	return (ft_strdup(ret));
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

void	*exp_error_fail(t_expander *expander)
{
	if (expander->err == EXP_ERR_MALLOC)
		print_shell_error(MALLOC_ERROR_MSG);
	if (expander->err == EXP_ERR_OTHER)
		print_shell_error("An error occurred in the expander");
	return (NULL);
}
