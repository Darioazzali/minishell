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

#ifndef ENV_H
# define ENV_H
# include "minishell.h"

typedef t_list	t_envs;

void			promote_var_to_env(t_envs *envs, char *name);
void			*free_sh_var(t_sh_var *env);
int				_env_malloc_err(t_sh_var *env);
void			export_var(t_envs *envs, char *name, char *value);
t_sh_var		*parse_variable_assignment(char *str);
#endif
