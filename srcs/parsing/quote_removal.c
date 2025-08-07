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

#include "parser.h"

static void	handle_quotes_removal(char *content);
static void	handle_double_quotes(char **read_ptr, char **write_ptr,
				t_parser_mode *mode);
static void	handle_single_quotes(char **read_ptr,
				char **write_ptr, t_parser_mode *mode);
static void	handle_normal_mode(char **read_ptr, char **write_ptr,
				t_parser_mode *mode);

/** Remove the quotes from the tokens in place*/
int	remove_quotes(t_ctx *ctx)
{
	t_list		*next;
	t_lexer		*parser;
	t_token		*tok;

	parser = ctx->lexer;
	parser->stage = P_QUOTES_REM;
	if (parser->tokens == NULL)
		return (-1);
	next = parser->tokens;
	while (next)
	{
		tok = next->content;
		handle_quotes_removal(tok->value);
		next = next->next;
	}
	log_debug("tokens with quotes removed:\n");
	log_debug_struct(parser->tokens, deb_format_tokens_type);
	return (0);
}

static void	handle_quotes_removal(char *token)
{
	char			*read_ptr;
	char			*write_ptr;
	t_parser_mode	mode;

	read_ptr = token;
	write_ptr = token;
	mode = LEXI_NORMAL;
	while (*read_ptr)
	{
		if (mode == LEXI_NORMAL)
			handle_normal_mode(&read_ptr, &write_ptr, &mode);
		else if (mode == LEXI_S_QUOTE)
			handle_single_quotes(&read_ptr, &write_ptr, &mode);
		else if (mode == LEXI_D_QUOTE)
			handle_double_quotes(&read_ptr, &write_ptr, &mode);
	}
	*write_ptr = '\0';
}

static void	handle_double_quotes(char **read_ptr, char **write_ptr,
							t_parser_mode *mode)
{
	if (**read_ptr == '\\' && *(*read_ptr + 1)
		&& *(*read_ptr + 1) == '"')
	{
		(*read_ptr)++;
		**write_ptr = **read_ptr;
		(*read_ptr)++;
		(*write_ptr)++;
	}
	else if (**read_ptr == '"')
	{
		*mode = LEXI_NORMAL;
		(*read_ptr)++;
	}
	else
	{
		**write_ptr = **read_ptr;
		(*write_ptr)++;
		(*read_ptr)++;
	}
}

static void	handle_single_quotes(char **read_ptr, char **write_ptr,
							t_parser_mode *mode)
{
	if (**read_ptr == '\'')
	{
		*mode = LEXI_NORMAL;
		(*read_ptr)++;
	}
	else
	{
		**write_ptr = **read_ptr;
		(*read_ptr)++;
		(*write_ptr)++;
	}
}

static void	handle_normal_mode(char **read_ptr, char **write_ptr,
							t_parser_mode *mode)
{
	if (**read_ptr == '\\' && *(*read_ptr + 1)
		&& (*(*read_ptr + 1) == '"' || *(*read_ptr + 1) == '\'' ))
	{
		(*read_ptr)++;
		**write_ptr = **read_ptr;
		(*read_ptr)++;
		(*write_ptr)++;
	}
	else if (**read_ptr == '"')
	{
		(*read_ptr)++;
		*mode = LEXI_D_QUOTE;
	}
	else if (**read_ptr == '\'')
	{
		(*read_ptr)++;
		*mode = LEXI_S_QUOTE;
	}
	else
	{
		**write_ptr = **read_ptr;
		(*read_ptr)++;
		(*write_ptr)++;
	}
}
