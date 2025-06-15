/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:33:55 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/14 14:34:59 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_token(t_ctx *ctx, char *start, char *end)
{
	t_list	*new;
	char	*new_str;

	new_str = ft_substr(start, 0, end - start + 1);
	if (!new_str)
		return (0);
	log_debug(ctx->logger, "Adding token");
	log_debug(ctx->logger, new_str);
	new = ft_lstnew(new_str);
	if (!new)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&ctx->tokenizer->tokens, new);
	return (1);
}
