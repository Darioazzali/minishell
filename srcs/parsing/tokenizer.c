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

void	init_tokenizer(t_lexer *tokenizer, const char *line)
{
	tokenizer->ptr = (char *)line;
	tokenizer->t_start = NULL;
	tokenizer->mode = LEXI_NORMAL;
	tokenizer->tokens = NULL;
	tokenizer->stage = P_TOKENIZING;
}

void	reset_tokenizer(t_lexer *tokenizer, const char *line)
{
	cleanup_tokenizer(tokenizer);
	tokenizer->ptr = (char *)line;
	tokenizer->t_start = NULL;
	tokenizer->mode = LEXI_NORMAL;
	tokenizer->tokens = NULL;
}

void	cleanup_tokenizer(t_lexer *tokenizer)
{
	void	(*free_fun)(void*);

	if (tokenizer->stage == P_TOKEN_REC)
		free_fun = free_token;
	else
		free_fun = free;
	ft_lstclear(&tokenizer->tokens, free_fun);
	tokenizer->tokens = NULL;
	if (tokenizer)
	{
		tokenizer->ptr = NULL;
		tokenizer->t_start = NULL;
	}
}
