/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 quote_removal.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/16 14:52:09 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/16 15:00:59 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "expander.h"

static char	*handle_quotes_removal(t_ctx *ctx, char *content);
static char	*handle_escapes_char(t_ctx *ctx, char *token);
static int	append_escaped_sym(t_expander *expander, char symbol);
static char	*ft_trim_double_quotes(char	*str);

int	remove_quotes(t_ctx *ctx)
{
	t_list		*next;
	t_tokenizer	*parser;
	char		*tmp;

	parser = ctx->parser;
	parser->stage = P_QUOTES_REM;
	if (parser->tokens == NULL)
		return (0);
	next = parser->tokens;
	while (next)
	{
		tmp = handle_quotes_removal(ctx, next->content);
		if (tmp == NULL)
			return (-1);
		free(next->content);
		next->content = tmp;
		next = next->next;
	}
	log_debug_struct(parser->tokens, deb_format_tokens);
	return (0);
}

static char	*handle_quotes_removal(t_ctx *ctx, char *token)
{
	char	*ret;
	char	*tmp;
	bool	single_quote;

	single_quote = false;
	if (*token == '\'')
		single_quote = true;
	if (single_quote)
		return (ft_strtrim(token, "'"));
	ret = ft_trim_double_quotes(token);
	if (!ret)
		return (NULL);
	tmp = handle_escapes_char(ctx, ret);
	if (!tmp)
	{
		free(ret);
		return (NULL);
	}
	free(ret);
	ret = tmp;
	return (ret);
}

static char	*handle_escapes_char(t_ctx *ctx, char *token)
{
	char		*ret;
	t_expander	expander;

	init_expander(&expander, ctx, token);
	while (*expander.cursor)
	{
		if (*expander.cursor == '\\' && *(expander.cursor + 1))
			append_escaped_sym(&expander, *(expander.cursor + 1));
		else
			expander.cursor++;
	}
	if (join_until_cursor(&expander) == -1)
		return (NULL);
	ret = expander.expanded;
	expander.expanded = NULL;
	return (ret);
}

static int	append_escaped_sym(t_expander *expander, char symbol)
{
	char	*tmp;
	char	s_char[2];

	s_char[0] = symbol;
	s_char[1] = '\0';
	if (join_until_cursor(expander) == -1)
		expand_err_code(expander, EXP_ERR_MALLOC, -1);
	tmp = ft_strjoin(expander->expanded, s_char);
	if (!tmp)
		expand_err_code(expander, EXP_ERR_MALLOC, -1);
	free(expander->expanded);
	expander->expanded = tmp;
	expander->cursor += 2;
	expander->start = expander->cursor;
	return (0);
}

static char	*ft_trim_double_quotes(char	*str)
{
	size_t	len;
	char	*res;

	if (*str != '"')
		return (ft_strdup(str));
	len = ft_strlen(str);
	res = ft_substr(str, 1, len - 2);
	return (res);
}
