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

#include "expander.h"

int	init_expander(t_expander *expander, t_ctx *ctx, const char *const token)
{
	expander->token = token;
	expander->cursor = (char *)token;
	expander->start = expander->cursor;
	expander->expanded = ft_strdup("");
	expander->mode = LEXI_NORMAL;
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
	char	*substr;
	int		start_idx;
	int		end_idx;

	start_idx = expander->start - expander->token;
	end_idx = expander->cursor - expander->start;
	substr = ft_substr(expander->token, start_idx, end_idx);
	if (!substr)
		return (expand_err_code(expander, EXP_ERR_MALLOC, -1));
	tmp = ft_strjoin(expander->expanded, substr);
	free(substr);
	if (!tmp)
		return (expand_err_code(expander, EXP_ERR_MALLOC, -1));
	free(expander->expanded);
	expander->expanded = tmp;
	return (0);
}

void	*clean_expander(t_expander *expander)
{
	if (expander->expanded)
	{
		free(expander->expanded);
		expander->expanded = NULL;
	}
	if (expander->err == EXP_ERR_MALLOC)
		print_shell_error(MALLOC_ERROR_MSG);
	if (expander->err == EXP_ERR_OTHER)
		print_shell_error("An error occurred in the expander");
	return (NULL);
}

char	*line_expansion(char *line, t_ctx *ctx)
{
	char	*res;

	res = expand_token(ctx, line);
	free(line);
	return (res);
}
