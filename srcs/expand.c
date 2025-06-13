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

static bool	is_single_quotes(char *token);
static char	*expand_if_var(char *str);

void	expand(t_ctx *ctx)
{
	t_parser	*parser;
	t_list		*token;

	parser = ctx->parser;
	token = parser->tokens;
	while (token)
	{
		if (!is_single_quotes(token->content))
			expand_if_var(token->content);
	}
}

static bool	is_single_quotes(char *token)
{
	if (token[0] == '\'')
		return (true);
	return (false);
}

static char	*expand_if_var(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr && *ptr != '$')
		ptr++;
	return (ptr);
}
