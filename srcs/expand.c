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

#include "parser.h"

static char	*expand_token(t_ctx *ctx, const char *token);
static int	append_shell_parameter(t_expander *expander);
static void	_debug_tokens(t_list *tokens);

int	expand_tokens(t_ctx *ctx)
{
	t_list		*token;
	char		*tmp;
	char		*first;

	token = ctx->parser->tokens;
	ctx->parser->stage = P_EXPANDING;
	while (token)
	{
		first = token->content;
		if (*first != '\'')
		{
			tmp = expand_token(ctx, token->content);
			if (!tmp)
			{
				print_shell_error(MALLOC_ERROR_MSG);
				return (-1);
			}
			free(token->content);
			token->content = tmp;
		}
		token = token->next;
	}
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
		if (*expander.cursor == '\\' && *(expander.cursor + 1) == '$')
			expander.cursor += 2;
		else if (*expander.cursor == '$')
			append_shell_parameter(&expander);
		else
			expander.cursor++;
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

static int	append_shell_parameter(t_expander *expander)
{
	char	*tmp;

	if (join_until_cursor(expander) == -1)
		expand_err_code(expander, EXP_ERR_MALLOC, -1);
	tmp = expand_shell_param(expander);
	if (!tmp)
		expand_err_code(expander, EXP_ERR_MALLOC, -1);
	expander->start = expander->cursor;
	expander->expanded = ft_strjoin(expander->expanded, tmp);
	free(tmp);
	if (!expander->expanded)
		expand_err_code(expander, EXP_ERR_MALLOC, -1);
	return (0);
}

static void	_debug_tokens(t_list *tokens)
{
	char	*fmt;

	fmt = deb_format_tokens(tokens);
	log_debug(fmt);
	free(fmt);
}
