/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 tokenizer.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/18 14:27:40 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/18 14:27:41 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static char	*handle_normal_mode(t_lexer *tokenizer, char *line);
static char	*handle_single_quotes(t_lexer *tokenizer, char *line);
static char	*handle_double_quotes(t_lexer *ctx, char *line);
static char	*scan_utill_boundary(t_lexer *tokenizer, char *line);

int	tokenize_line(t_lexer *tokenizer, const char *line)
{
	init_tokenizer(tokenizer, line);
	if (!tokenizer)
		return (-1);
	while (*tokenizer->ptr)
	{
		if (tokenizer->mode == LEXI_NORMAL)
		{
			skip_whitespace(tokenizer);
			if (!*tokenizer->ptr)
				break ;
			tokenizer->ptr = handle_normal_mode(tokenizer, tokenizer->ptr);
		}
		else if (tokenizer->mode == LEXI_D_QUOTE)
			tokenizer->ptr = handle_double_quotes(tokenizer, tokenizer->ptr);
		else if (tokenizer->mode == LEXI_S_QUOTE)
			tokenizer->ptr = handle_single_quotes(tokenizer, tokenizer->ptr);
	}
	if (tokenizer->t_start)
		add_token(tokenizer, tokenizer->ptr);
	if (tokenizer->mode != LEXI_NORMAL)
		return (print_shell_error_ret_int("error: Unterminated quotes", -1));
	return (0);
}

static	char	*handle_normal_mode(t_lexer *tokenizer, char *line)
{
	if (*line && is_metachar(line))
	{
		if (tokenizer->t_start)
			add_token(tokenizer, line);
		tokenizer->t_start = line;
		return (handle_metachar(tokenizer, line));
	}
	if (!tokenizer->t_start)
		tokenizer->t_start = line;
	line = scan_utill_boundary(tokenizer, line);
	if (tokenizer->t_start && tokenizer->mode == LEXI_NORMAL)
		add_token(tokenizer, line);
	return (line);
}

static char	*scan_utill_boundary(t_lexer *tokenizer, char *line)
{
	while (*line && !is_metachar(line) && *line != ' ')
	{
		if (*line == '\\' && (*(line + 1) == '\"'
				|| (*line + 1) != '\''))
			line++;
		else if (*line == '\'')
		{
			tokenizer->mode = LEXI_S_QUOTE;
			return (line);
		}
		else if (*line == '"')
		{
			tokenizer->mode = LEXI_D_QUOTE;
			return (line);
		}
		line++;
	}
	return (line);
}

static	char	*handle_single_quotes(t_lexer *tokenizer, char *line)
{
	line++;
	while (*line)
	{
		if (*line == '\'')
		{
			tokenizer->mode = LEXI_NORMAL;
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

static	char	*handle_double_quotes(t_lexer *tokenizer, char *line)
{
	line++;
	while (*line)
	{
		if (*line == '\\' && (*(line + 1) == '\"'))
			line = (line + 2);
		else if (*line == '"')
		{
			tokenizer->mode = LEXI_NORMAL;
			break ;
		}
		else
			line++;
	}
	line++;
	return (line);
}
