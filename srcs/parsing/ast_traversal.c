/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:23:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/25 15:40:49 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	traverse_ast(t_ast_node	*node,
				void (*visit)(t_ast_node *, void*), void *ctx)
{
	if (!node)
		return (0);
	visit(node, ctx);
	return (1);
}
