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

static void	handle_quotes_removal(char *content);
// static char	*handle_escapes_char(t_ctx *ctx, char *token);
// static int	append_escaped_sym(t_expander *expander, char symbol);
// static char	*ft_trim_double_quotes(char	*str);
static void	handle_double_quotes(char **read_ptr, char **write_ptr,
				t_parser_mode *mode);

int	remove_quotes(t_ctx *ctx)
{
	t_list		*next;
	t_lexer		*parser;

	parser = ctx->lexer;
	parser->stage = P_QUOTES_REM;
	if (parser->tokens == NULL)
		return (0);
	next = parser->tokens;
	while (next)
	{
		handle_quotes_removal(next->content);
		next = next->next;
	}
	log_debug_struct(parser->tokens, deb_format_tokens);
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
		{
			if (*read_ptr == '\\' && *(read_ptr + 1)
				&& (*(read_ptr + 1) != '"'
					|| *(read_ptr + 1) != '\'' )
			)
			{
				read_ptr++;
				*(write_ptr) = *read_ptr;
				read_ptr++;
				write_ptr++;
			}
			else if (*read_ptr == '"')
			{
				mode = LEXI_D_QUOTE;
				read_ptr++;
			}
			else if (*read_ptr == '\'')
			{
				mode = LEXI_S_QUOTE;
				read_ptr++;
			}
			else
			{
				*(write_ptr) = *read_ptr;
				read_ptr++;
				write_ptr++;
			}
		}
		else if (mode == LEXI_S_QUOTE)
		{
			if (*read_ptr == '\'')
			{
				mode = LEXI_NORMAL;
				read_ptr++;
			}
			else
			{
				(*write_ptr) = *read_ptr;
				read_ptr++;
				write_ptr++;
			}
		}
		else if (mode == LEXI_D_QUOTE)
		{
			handle_double_quotes(&read_ptr, &write_ptr, &mode);
		}
	}
	*write_ptr = '\0';
}

static void	handle_double_quotes(char **read_ptr, char **write_ptr, t_parser_mode *mode)
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
