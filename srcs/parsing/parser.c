/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/02 07:57:01 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_parser(t_ctx *ctx)
{
	if (!ctx->lexer)
		return (NULL);
	if (ctx->lexer->tokens)
		ft_lstclear(&ctx->lexer->tokens, free);
	free(ctx->lexer);
	return (NULL);
}
