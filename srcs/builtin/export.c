/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 export.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/02 10:00:25 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/03 09:16:51 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static int	_handle_assignment(char *arg, t_envs *envs);

/** @brief Export shell builtin
 *
 * Promote a shell variable to environment variable or define
 * 			a new environment variable in the form
 * 			KEY=VALUE
 *
 * 	@note. The export program accept:
 * 	1. No argument -> The program print the environment variables
 * 	2. One argument or more arguments -> 
 * 		The program promote the shell variable to environment variable
 * 		or if is in the form KEY=VALUE it will be define and then promoted
 * 		as env.
 * 	
 * */
int	export_btin(char **av, t_envs *envs)
{
	int		status;

	status = 0;
	if (!av || !av[0])
	{
		print_vars(envs, true);
		return (0);
	}
	while (*av)
	{
		if (ft_strchr(*av, '='))
			status |= _handle_assignment(*av, envs);
		else
		{
			if (is_valid_var_name(*av))
				promote_var_to_env(envs, *av);
			else
				status |= 1;
		}
		av++;
	}
	return (status);
}

void	export_var(t_envs *envs, char *name, char *value)
{
	t_sh_var	*env;

	if (!name)
		return ;
	if (!value)
	{
		env = get_shell_var(envs, name);
		if (env)
		{
			env->exported = true;
			return ;
		}
	}
	set_shell_var(envs, name, value);
	promote_var_to_env(envs, name);
}

/** 
 * @brief Handle assignment
 *
 * Handle the assignment of a variable in the form KEY=VALUE
 * @return 1 on error and 0 on success
 * */
static int	_handle_assignment(char *arg, t_envs *envs)
{
	t_sh_var	*env;

	env = parse_variable_assignment(arg);
	if (!env)
		return (1);
	export_var(envs, env->name, env->value);
	free_sh_var(env);
	return (0);
}
