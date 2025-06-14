/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/14 08:59:42 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_parser(t_ctx *ctx)
{
	if (!ctx->tokenizer)
		return (NULL);
	if (ctx->tokenizer->tokens)
		ft_lstclear(&ctx->tokenizer->tokens, free);
	free(ctx->tokenizer);
	return (NULL);
}
