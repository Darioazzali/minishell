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

static char	*expand_if_var(char *str);
// static char	*handle_metachar(char *ptr);
static bool	is_metachar(char *ptr);
static char	*handle_variable(char **ptr);
static char	*join_all(char *res, char *str, char *ptr, char *start);

void	expand(t_ctx *ctx)
{
	t_parser	*parser;
	t_list		*token;
	char		*first;

	parser = ctx->parser;
	token = parser->tokens;
	while (token)
	{
		first = token->content;
		if (*first == '\'')
			expand_if_var(token->content);
		token = token->next;
	}
}

static char	*expand_if_var(char *str)
{
	char	*ptr;
	char	*res;
	char	*start;

	ptr = str;
	start = str;
	res = ft_strdup("");
	while (*ptr)
	{
		if (*ptr != '$')
			ptr++;
		else
		{
			res = join_all(res, str, ptr, start);
			start = ptr;
			if (*ptr && is_metachar(ptr))
			{
				ptr++;
			}
			res = handle_variable(&ptr);
		}
	}
	return (res);
}

static char	*join_all(char *res, char *str, char *ptr, char *start)
{
	char	*tmp;
	char	*raw;

	raw = ft_substr(str, start - str, ptr - start);
	if (!raw)
		return (NULL);
	tmp = ft_strjoin(res, raw);
	if (!tmp)
	{
		free(raw);
		return (NULL);
	}
	free(res);
	free(raw);
	return (ptr);
}

// static char	*handle_metachar(char *ptr)
// {
// 	char	*expansion;
//
// 	expansion = ft_strdup("");
// 	(*ptr)++;
// 	return (expansion);
// }

static bool	is_metachar(char *ptr)
{
	if (*ptr == '$' || *ptr == '?'
		|| *ptr == '@' || *ptr == '#'
		|| ft_isdigit(*ptr) || *ptr == '*'
		|| *ptr == '!')
		return (true);
	return (false);
}

static char	*handle_variable(char **ptr)
{
	(*ptr)++;
	return (ft_strdup(""));
}
