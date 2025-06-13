/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/13 20:27:54 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_parser(t_ctx *ctx)
{
	if (!ctx->parser)
		return (NULL);
	if (ctx->parser->tokens)
		ft_lstclear(&ctx->parser->tokens, free);
	free(ctx->parser);
	return (NULL);
}

