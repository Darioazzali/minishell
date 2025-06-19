/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 token_recognizing.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/18 12:46:29 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/18 12:56:43 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static void			*recognize_token(void *token);
static t_tok_type	get_type(char *token);

int	recognize_tokens(t_ctx *ctx)
{
	t_list	*token;
	t_list	*ret;

	token = ctx->tokenizer->tokens;
	ret = ft_lstmap(token, recognize_token, free);
	if (!ret)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		return (-1);
	}
	ft_lstclear(&ctx->tokenizer->tokens, free);
	ctx->tokenizer->tokens = ret;
	log_debug(ctx->logger, "Quotes removed");
	log_debug(ctx->logger, deb_format_tokens_type(ctx->tokenizer->tokens));
	return (0);
}

static void	*recognize_token(void *token)
{
	char	*t;
	t_token	*tok;

	t = token;
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = get_type(t);
	tok->value = ft_strdup(t);
	return (tok);
}

static t_tok_type	get_type(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (TOK_REDIR_APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (TOK_REDIR_HEREDOC);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (TOK_AND);
	if (token[0] == '|')
		return (TOK_PIPE);
	if (token[0] == '&')
		return (TOK_AND);
	else if (token[0] == '>')
		return (TOK_REDIR_OUT);
	else if (token[0] == '<')
		return (TOK_REDIR_IN);
	return (TOK_WORD);
}
