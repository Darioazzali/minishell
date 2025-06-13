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

static char	*expand_if_var(const char *str);
// static char	*handle_metachar(char **ptr);
// static bool	is_metachar(char *ptr);
static char	*handle_variable(char **ptr);
static char	*join_new_part(char *res, const char *str, char *ptr, char *start);

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
		if (*first != '\'')
			token->content = expand_if_var(token->content);
		token = token->next;
	}
	log_debug(ctx->logger, deb_format_tokens(parser->tokens));
}

static char	*expand_if_var(const char *str)
{
	char	*ptr;
	char	*res;
	char	*start;
	char	*tmp;
	bool	escaping_mode;

	escaping_mode = false;
	ptr = (char *)str;
	start = (char *)str;
	res = ft_strdup("");
	while (*ptr)
	{
		if (*ptr == '\\' && !escaping_mode)
		{
			escaping_mode = true;
			res = join_new_part(res, str, ptr, start);
			ptr++;
			start = ptr;
		}
		else if (*ptr == '$' && !escaping_mode)
		{
			res = join_new_part(res, str, ptr, start);
			ptr++;
			tmp = handle_variable(&ptr);
			start = ptr;
			res = ft_strjoin(res, tmp);
		}
		else
		{
			escaping_mode = false;
			ptr++;
		}
	}
	res = join_new_part(res, str, ptr, start);
	return (res);
}

/**
 * @brief Join the substring to the result of the precedent expansions
 *
 * @param previous The previous string
 * @param str The beginning of the token
 * @param ptr The address of the actual position in the token
 * @param start The start of the substring that we want to join
	*
	* */
static char	*join_new_part(char *previous,
						const char *token, char *end_ptr, char *start)
{
	char	*tmp;
	char	*raw;

	raw = ft_substr(token, start - token, end_ptr - start);
	if (!raw)
		return (NULL);
	tmp = ft_strjoin(previous, raw);
	if (!tmp)
	{
		free(raw);
		return (NULL);
	}
	free(previous);
	free(raw);
	return (tmp);
}

static char	*handle_variable(char **ptr)
{
	char	*ret;
	char	*start;
	char	*tmp;

	start = *ptr;
	while (**ptr && (ft_isdigit(**ptr) || ft_isalpha(**ptr)))
		(*ptr)++;
	tmp = ft_substr(start, 0, *ptr - start);
	if (!tmp)
		return (NULL);
	ret = getenv(tmp);
	free(tmp);
	if (!ret)
	{
		free(ret);
		return (ft_strdup(""));
	}
	return (ret);
}

// static char	*handle_metachar(char **ptr)
// {
// 	char	*expansion;
//
// 	expansion = ft_strdup("There is a meta frate");
// 	*ptr = (*ptr + 2);
// 	return (expansion);
// }

// static bool	is_metachar(char *ptr)
// {
// 	if (*ptr == '$' || *ptr == '?'
// 		|| *ptr == '@' || *ptr == '#'
// 		|| ft_isdigit(*ptr) || *ptr == '*'
// 		|| *ptr == '!')
// 		return (true);
// 	return (false);
// }
