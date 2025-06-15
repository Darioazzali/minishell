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
static void		revert_if_space(char **line);

int	tokenize_line(t_ctx *ctx, const char *line)
{
	t_parser	*tokenizer;

	ctx->tokenizer = malloc(sizeof(t_parser));
	if (!ctx->tokenizer)
		return (-1);
	tokenizer = ctx->tokenizer;
	tokenizer->ptr = (char *)line;
	tokenizer->mode = LEXI_NORMAL;
	tokenizer->tokens = NULL;
	while (*tokenizer->ptr)
	{
		if (ctx->tokenizer->mode == LEXI_NORMAL)
		{
			while (*tokenizer->ptr && *tokenizer->ptr == ' ')
				tokenizer->ptr++;
			tokenizer->ptr = handle_normal_mode(ctx, tokenizer->ptr);
		}
		else if (tokenizer->mode == LEXI_D_QUOTE)
			tokenizer->ptr = handle_double_quotes(ctx, tokenizer->ptr);
		else if (ctx->tokenizer->mode == LEXI_S_QUOTE)
			tokenizer->ptr = handle_single_quotes(ctx, tokenizer->ptr);
	}
	if (ctx->tokenizer->mode != LEXI_NORMAL)
		return (-1);
	return (0);
}

static	char	*handle_normal_mode(t_ctx *ctx, char *line)
{
	char	*start;

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
	revert_if_space(&line);
	add_token(ctx, start, line);
	if (*(line + 1) == ' ')
		line++;
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

static	char	*handle_double_quotes(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	line++;
	log_debug(ctx->logger, "Entering double quotes");
	while (*line)
	{
		if (*line == '\\' && (*(line + 1) == '\"'))
			line = (line + 2);
		else if (*line == '"')
		{
			ctx->tokenizer->mode = LEXI_NORMAL;
			break ;
		}
		else
			line++;
	}
	add_token(ctx, start, line + 1);
	line++;
	log_debug(ctx->logger, "Exiting double quotes");
	return (line);
}

static void	revert_if_space(char **line)
{
	if (**line == ' ')
		(*line)--;
}
