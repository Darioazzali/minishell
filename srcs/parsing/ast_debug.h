/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:39:31 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/29 10:24:44 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_DEBUG_H
# define AST_DEBUG_H

# include "ast.h"

void				debug_ast_command_args(char *line, t_ast_node *node);
void				append_node_type(char *line, t_ast_node *node);
void				debug_ast_command_redirs(char *line,
						t_ast_node *node, int depth);
void				debug_ast_commands_fds(char *line,
						t_ast_node *node, int depth);
#endif
