/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:27:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/13 14:23:14 by dazzali          ###   ########.fr       */
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

// static	char	*read_var(t_ctx *ctx, char **ptr)
// {
// 	char	*var;
// 	char	*tmp;
// 	char	*val;
// 	size_t	len;
//
// 	log_debug(ctx->logger, "Reading var");
// 	log_debug(ctx->logger,*ptr);
// 	tmp = *ptr;
// 	len = 0;
// 	while (*tmp && (*tmp != ' ' && *tmp != '\t' && *tmp != '\"'))
// 	{
// 		len++;
// 		tmp++;
// 	}
// 	if (!len)
// 	{
// 		return (NULL);
// 	}
// 	var = malloc(len + 1);
// 	ft_strlcpy(var, *ptr, len + 1);
// 	var[len] = '\0';
// 	val = getenv(var);
// 	free(var);
// 	*ptr = tmp;
// 	return (val);
// }
