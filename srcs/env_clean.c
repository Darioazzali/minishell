/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env3.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/16 15:34:02 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/16 15:36:40 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static void	free_env_node(void *content);

/** @brief Free the memory allocated for the environment list
 *	
 *	Free the environment list and its content.
 *
 * */
void	*free_envs(t_envs *envs)
{
	ft_lstclear(&envs, free_env_node);
	return (NULL);
}

static void	free_env_node(void *content)
{
	free_sh_var((t_sh_var *)content);
}

/** @brief free the shell var memory
 *
 * Free the shell variable and its content.
 *
 * @param var A pointer to the shell variable
 *
 * */
void	*free_sh_var(t_sh_var *var)
{
	if (!var)
		return (NULL);
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	return (NULL);
}

/** @brief Clean the shell variable memory and print an error message
 *  Utility function to handle malloc errors for shell variables.
 *
 *  @return 1
 * */
int	_env_malloc_err(t_sh_var *env)
{
	print_error(MALLOC_ERROR_MSG);
	free_sh_var(env);
	return (1);
}
