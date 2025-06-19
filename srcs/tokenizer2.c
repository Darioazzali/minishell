/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 tokenizer2.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 14:33:55 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/16 16:41:49 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static bool	is_empty(char *start, char *end);

int	add_token(t_ctx *ctx, char *start, char *end)
{
	t_list	*new;
	char	*new_str;

	if (is_empty(start, end))
		return (0);
	new_str = ft_substr(start, 0, end - start);
	if (!new_str)
		return (0);
	log_debug(ctx->logger, "Adding token");
	new = ft_lstnew(new_str);
	if (!new)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&ctx->tokenizer->tokens, new);
	return (1);
}

static bool	is_empty(char *start, char *end)
{
	while (start < end)
	{
		if (!ft_is_whitespace(*start))
			return (false);
		start++;
	}
	return (true);
}

bool	is_metachar(char *c)
{
	if (ft_strncmp(c, ">>", 2) == 0
		|| ft_strncmp(c, "<<", 2) == 0
		|| ft_strncmp(c, "&&", 2) == 0)
		return (true);
	if (*c == ' ' || *c == '&' || *c == '>' || *c == '<' || *c == '|')
		return (true);
	return (false);
}

char	*handle_metachar(t_ctx *ctx, char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0
		|| ft_strncmp(line, "<<", 2) == 0
		|| ft_strncmp(line, "&&", 2) == 0)
	{
		add_token(ctx, line, line + 2);
		return (line + 2);
	}
	else
	{
		add_token(ctx, line, line + 1);
		return (line + 1);
	}
}
