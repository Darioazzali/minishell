/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expand.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/13 13:41:44 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/13 13:44:12 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "expander.h"

static char	*expand_token(t_ctx *ctx, const char *token);
static void	_debug_tokens(t_list *tokens);

int	expand_tokens(t_ctx *ctx)
{
	t_list		*token;
	char		*tmp;

	token = ctx->parser->tokens;
	ctx->parser->stage = P_EXPANDING;
	while (token)
	{
		tmp = expand_token(ctx, token->content);
		if (!tmp)
		{
			print_shell_error(MALLOC_ERROR_MSG);
			return (-1);
		}
		free(token->content);
		token->content = tmp;
		token = token->next;
	}
	log_debug("expanded tokens:\n");
	_debug_tokens(ctx->parser->tokens);
	return (0);
}

static char	*expand_token(t_ctx *ctx, const char *token)
{
	t_expander	expander;
	char		*ret;

	init_expander(&expander, ctx, token);
	while (*expander.cursor)
	{
		exp_process_char(&expander);
		if (expander.err != EXP_NO_ERROR)
			return (exp_error_fail(&expander));
	}
	join_until_cursor(&expander);
	if (expander.err != EXP_NO_ERROR)
		return (exp_error_fail(&expander));
	ret = ft_strdup(expander.expanded);
	free(expander.expanded);
	if (!ret)
		print_shell_error(MALLOC_ERROR_MSG);
	return (ret);
}

/* @brief Append shell parameter to the expanded token
 * Append the character processed, expand the shell variable/parameter
 * and append it to the string.
 * The cursor is advanced to the end of the shell variable/parameter.
 * */
void	append_shell_variable(t_expander *expander)
{
	char	*tmp;
	char	*old_expanded;

	if (join_until_cursor(expander) == -1)
		return (set_expander_error(expander, EXP_ERR_MALLOC));
	tmp = expand_shell_param(expander);
	if (!tmp)
		return (set_expander_error(expander, EXP_ERR_MALLOC));
	expander->start = expander->cursor;
	old_expanded = expander->expanded;
	expander->expanded = ft_strjoin(expander->expanded, tmp);
	free(old_expanded);
	free(tmp);
	if (!expander->expanded)
		return (set_expander_error(expander, EXP_ERR_MALLOC));
}

static void	_debug_tokens(t_list *tokens)
{
	char	*fmt;

	fmt = deb_format_tokens(tokens);
	log_debug(fmt);
	free(fmt);
}
