/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 15:14:32 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 17:22:24 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static char		*handle_normal_mode(t_ctx *ctx, char *line);
static char		*handle_single_quotes(t_ctx *ctx, char *line);
static char		*handle_double_quotes(t_ctx *ctx, char *line);
static int		add_token(t_ctx *ctx, char *start, char *end);

int	tokenize_line(t_ctx *ctx, char *line)
{
	t_parser	*tokenizer;

	ctx->tokenizer = malloc(sizeof(t_parser));
	if (!ctx->tokenizer)
		return (-1);
	tokenizer = ctx->tokenizer;
	tokenizer->ptr = line;
	tokenizer->mode = LEXI_NORMAL;
	tokenizer->tokens = NULL;
	while (*tokenizer->ptr)
	{
		if (ctx->tokenizer->mode == LEXI_NORMAL)
			tokenizer->ptr = handle_normal_mode(ctx, tokenizer->ptr);
		else if (tokenizer->mode == LEXI_D_QUOTE)
			tokenizer->ptr = handle_double_quotes(ctx, tokenizer->ptr);
		else if (ctx->tokenizer->mode == LEXI_S_QUOTE)
			tokenizer->ptr = handle_single_quotes(ctx, tokenizer->ptr);
	}
	if (ctx->tokenizer->mode != LEXI_NORMAL)
	{
		log_error(ctx->logger, "Error, unterminated quote");
		return (-1);
	}
	return (0);
}

static	char	*handle_double_quotes(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	line++;
	while (*line)
	{
		if (*line == '"')
		{
			log_debug(ctx->logger, "Exiting double quote mode");
			ctx->tokenizer->mode = LEXI_NORMAL;
			break ;
		}
		line++;
	}
	add_token(ctx, start, line + 1);
	line++;
	log_debug(ctx->logger, "Exiting normal mode");
	return (line);
}

static	char	*handle_normal_mode(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	while (*line && *line == ' ')
		line++;
	start = line;
	while (*line && *line != ' ')
	{
		if (*line == '\\' && ((*line + 1) == '\"'
				|| (*line + 1) != '\''))
			line++;
		else if (*line == '\'')
		{
			ctx->tokenizer->mode = LEXI_S_QUOTE;
			return (line);
		}
		else if (*line == '"')
		{
			ctx->tokenizer->mode = LEXI_D_QUOTE;
			return (line);
		}
		line++;
	}
	add_token(ctx, start, line);
	return (line);
}

static	char	*handle_single_quotes(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	line++;
	while (*line)
	{
		if (*line == '\'')
		{
			add_token(ctx, start, line);
			ctx->tokenizer->mode = LEXI_NORMAL;
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

static int	add_token(t_ctx *ctx, char *start, char *end)
{
	t_list	*new;
	char	*new_str;

	new_str = ft_substr(start, 0, end - start + 1);
	if (!new_str)
		return (0);
	new = ft_lstnew(new_str);
	if (!new)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&ctx->tokenizer->tokens, new);
	return (1);
}
