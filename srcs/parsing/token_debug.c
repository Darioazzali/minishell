/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:18:14 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/19 11:22:35 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

t_buffer_ctx	init_buffer_ctx(char *buffer, char *ptr, int total_len)
{
	t_buffer_ctx	ctx;

	ctx.start = buffer;
	ctx.ptr = ptr;
	ctx.remaining = total_len;
	ctx.total_len = total_len - (ptr - buffer);
	return (ctx);
}

void	append_to_buffer(t_buffer_ctx *ctx, const char *str)
{
	ft_strlcpy(ctx->ptr, str, ctx->remaining);
	ctx->ptr += ft_strlen(ctx->ptr);
	ctx->remaining = ctx->total_len - (ctx->ptr - ctx->start);
}
