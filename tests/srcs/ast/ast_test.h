/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:47:48 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/25 14:07:33 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TEST_H
# define AST_TEST_H
# include "ast.h"
# include "test.h"
# include <assert.h>

typedef struct s_test
{
	char	*name;
	char	*line;
	char	*expected;
	t_ctx	*ctx;
}	t_test;

t_list	*parse_test_file(char *path);

extern char	g_buff[1024];

void	test_visit(t_ast_node *node, void *ctx);
void	test_visit(t_ast_node *node, void *ctx);
#endif
