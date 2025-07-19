/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_debug.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 17:12:36 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 17:13:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"
#include "debug.h"

static t_token	*extract_token(t_list *lst);
static char		*format_token_struct(t_list *tok);

char	*deb_format_tokens(t_list *lst)
{
	t_list	*tmp;
	char	*str;
	char	*fmt;
	char	*old_fmt;

	if (!DEBUG)
		return (NULL);
	tmp = lst;
	fmt = ft_strdup("Tokens:");
	while (tmp)
	{
		old_fmt = fmt;
		fmt = ft_strjoin(fmt, "\n");
		free(old_fmt);
		str = (char *)tmp->content;
		old_fmt = fmt;
		fmt = ft_strjoin(fmt, str);
		free(old_fmt);
		tmp = tmp->next;
	}
	return (fmt);
}

char	*deb_format_tokens_type(t_list *lst)
{
	t_list	*tmp;
	char	*str;
	char	*fmt;
	char	*old_fmt;

	if (!DEBUG)
		return (NULL);
	tmp = lst;
	fmt = ft_strdup("Tokens:");
	while (tmp)
	{
		fmt = ft_strjoin(fmt, "\n");
		str = format_token_struct(tmp);
		old_fmt = fmt;
		fmt = ft_strjoin(fmt, str);
		free(old_fmt);
		free(str);
		tmp = tmp->next;
	}
	return (fmt);
}

char	*get_token_type_str(t_tok_type tok)
{
	if (tok == TOK_PIPE)
		return ("PIPE");
	if (tok == TOK_REDIR_APPEND)
		return ("REDIRECT APPEND");
	if (tok == TOK_REDIR_HEREDOC)
		return ("HEREDOC");
	if (tok == TOK_REDIR_IN)
		return ("REDIRECT IN");
	if (tok == TOK_REDIR_OUT)
		return ("REDIRECT OUT");
	if (tok == TOK_OR)
		return ("OR");
	if (tok == TOK_AND)
		return ("AND");
	return ("TOK_WORD");
}

static char	*format_token_struct(t_list *tok)
{
	t_buffer_ctx	ctx;
	t_token			*token;
	char			*formatted;
	int				total_len;

	token = extract_token(tok);
	total_len = strlen("{\n  token_value: \n  token_type:  \n}")
		+ ft_strlen(token->value)
		+ ft_strlen(get_token_type_str(token->type)) + 100;
	formatted = malloc(total_len);
	if (!formatted)
		return (NULL);
	ctx = init_buffer_ctx(formatted, formatted, total_len);
	append_to_buffer(&ctx, "{\n  " TOKEN_VALUE_LABEL);
	append_to_buffer(&ctx, token->value);
	append_to_buffer(&ctx, RESET "\n  " TOKEN_TYPE_LABEL);
	append_to_buffer(&ctx, get_token_type_str(token->type));
	append_to_buffer(&ctx, RESET "\n}");
	return (formatted);
}

static	t_token	*extract_token(t_list *lst)
{
	t_token	*ret;

	ret = lst->content;
	return (ret);
}
