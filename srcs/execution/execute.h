/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execute.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/27 11:07:29 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/29 08:26:05 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "ast.h"

typedef struct s_exec_ctx
{
	int			next_input_fd;
	t_ast_node	*pending_command;
	t_list		*pipes_fds;
	int			pipe_count;
	t_ctx		*ctx;
}	t_exec_ctx;

typedef struct s_pipeline_exec_ctx
{
	int		*pids;
	int		pid_count;
	int		max_pids;
	t_ctx	*shell_ctx;
}	t_pipeline_exec_ctx;

int		execute_single_command(t_ast_node *node, t_ctx *ctx, char *prog_name);
char	*resolve_exec_path(char *prog_name, t_ctx *ctx);
t_list	*flatten_pipeline_subtree(t_ast_node *node);
void	execute_child_proc(char *prog_name, char **args, t_ctx *ctx);;
char	**build_args(t_ast_node *node);
void	handle_pipeline(t_list *node, t_ctx *ctx);
int		handle_redirections(t_ast_node *node);
int		manage_pipeline_fds(t_ast_node *node, int *open_fds, int opened_fds);
int		execute_btin(char *prog_name, char **args, t_ctx *ctx);
bool	is_builtin(char *command);

#endif
