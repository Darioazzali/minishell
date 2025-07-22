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

	token = ctx->parser->tokens;
	ctx->parser->stage = P_TOKEN_REC;
	ret = ft_lstmap(token, recognize_token, free);
	if (!ret)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		return (-1);
	}
	ft_lstclear(&ctx->parser->tokens, free);
	ctx->parser->tokens = ret;
	log_debug_struct(ctx->parser->tokens, deb_format_tokens_type);
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

void	free_token(void *token)
{
	t_token	*t;

	t = token;
	free(t->value);
	free(t);
}
