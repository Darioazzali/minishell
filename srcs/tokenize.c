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

static char	*handle_normal_mode(t_parser *tokenizer, char *line);
static char	*handle_single_quotes(t_parser *tokenizer, char *line);
static char	*handle_double_quotes(t_parser *ctx, char *line);

int	tokenize_line(t_parser *tokenizer, const char *line)
{
	init_tokenizer(tokenizer, line);
	if (!tokenizer)
		return (-1);
	while (*tokenizer->ptr)
	{
		if (tokenizer->mode == LEXI_NORMAL)
		{
			while (*tokenizer->ptr && *tokenizer->ptr == ' ')
				tokenizer->ptr++;
			tokenizer->ptr = handle_normal_mode(tokenizer, tokenizer->ptr);
		}
		else if (tokenizer->mode == LEXI_D_QUOTE)
			tokenizer->ptr = handle_double_quotes(tokenizer, tokenizer->ptr);
		else if (tokenizer->mode == LEXI_S_QUOTE)
			tokenizer->ptr = handle_single_quotes(tokenizer, tokenizer->ptr);
	}
	if (tokenizer->mode != LEXI_NORMAL)
		return (-1);
	return (0);
}

static	char	*handle_normal_mode(t_parser *tokenizer, char *line)
{
	char	*start;

	if (*line && is_metachar(line))
		return (handle_metachar(tokenizer, line));
	start = line;
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
	add_token(tokenizer, start, line);
	return (line);
}

static	char	*handle_single_quotes(t_parser *tokenizer, char *line)
{
	char	*start;

	start = line;
	line++;
	while (*line)
	{
		if (*line == '\'')
		{
			add_token(tokenizer, start, line + 1);
			tokenizer->mode = LEXI_NORMAL;
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

static	char	*handle_double_quotes(t_parser *tokenizer, char *line)
{
	char	*start;

	start = line;
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
	add_token(tokenizer, start, line + 1);
	line++;
	return (line);
}
