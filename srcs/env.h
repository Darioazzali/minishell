/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env.h												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/01 13:59:50 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/01 13:59:57 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

typedef t_list	t_envs;

void	promote_var_to_env(t_envs *envs, char *name);
void	print_vars(t_envs *envs, bool only_envs);
void	*free_env(t_env *env);
void	free_split_result(char **split_result);
