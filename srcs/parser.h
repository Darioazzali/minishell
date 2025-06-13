/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 12:04:44 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 19:10:45 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "log.h"

typedef enum e_lexi
{
	LEXI_S_QUOTE,
	LEXI_D_QUOTE,
	LEXI_NORMAL
}	t_parser_mode;

typedef enum e_tok_type
{
	TOK_VAR,
	TOK_NORMAL
}	t_tok_type;

typedef struct s_parser
{
	t_parser_mode	mode;
	char			*ptr;
	t_list			*tokens;
}	t_parser;

typedef struct s_token
{
	t_tok_type	type;
	char		*value;
}	t_token;

char	*deb_format_tokens(t_list *lst);
void	*free_parser(t_ctx *ctx);
#endif
