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
	else
		return ("TOK_WORD");
}

static char	*format_token_struct(t_list *tok)
{
	char	*ret;
	char	*tmp;

	ret = ft_strdup("{\n");
	tmp = ret;
	ret = ft_strjoin(tmp, extract_token(tok)->value);
	ret = ft_strjoin(ret, "\n");
	ret = ft_strjoin(ret, get_token_type_str(extract_token(tok)->type));
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, "\n");
	ret = ft_strjoin(ret, "}");
	free(tmp);
	return (ret);
}

static	t_token	*extract_token(t_list *lst)
{
	t_token	*ret;

	ret = lst->content;
	return (ret);
}
