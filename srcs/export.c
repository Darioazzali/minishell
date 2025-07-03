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

static bool	is_valid_var(char *str);
static bool	is_assignment(char *str);
int			split_assignment(char *str, char **name, char **val);

void	_export(char **av, t_envs *envs)
{
	char	*var_name;
	char	*var_value;

	(void)av;
	if (!av)
	{
		print_vars(envs, true);
		return ;
	}
	while (*av)
	{
		if (is_assignment(*av))
		{
			if (split_assignment(*av, &var_name, &var_value) != 0)
			{
				print_shell_error(MALLOC_ERROR_MSG);
				return ;
			}
			if (!is_valid_var(var_name))
			{
				free(var_name);
				free(var_value);
				print_shell_error("Invalid variable name");
				return ;
			}
			_export_var(envs, var_name, var_value);
		}
		else
		{
			if (!is_valid_var(*av))
				promote_var_to_env(envs, *av);
			else
				print_shell_error("Invalid variable name");
		}
		av++;
	}
}

/** @brief check if the variable is valid
 *
 * Check if the variable name is valid being compliant with posix
 * */
static bool	is_valid_var(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	_export_var(t_envs *envs, char *name, char *value)
{
	t_env	*env;

	if (!name)
		return ;
	if (!value)
	{
		env = get_shell_var(envs, name);
		if (env)
		{
			env->exported = true;
		}
	}
	set_shell_var(envs, name, value);
	promote_var_to_env(envs, name);
}

/** Check if the variable is an assignment */
static bool	is_assignment(char *str)
{
	char	*equals;

	equals = ft_strchr(str, '=');
	if (!equals || equals == str)
		return (false);
	return (true);
}

int	split_assignment(char *str, char **name, char **val)
{
	int	eq_idx;

	eq_idx = ft_strchr(str, '=') - str;
	*name = ft_substr(str, 0, eq_idx);
	if (!*name)
		return (1);
	*val = ft_substr(str, eq_idx + 1, ft_strlen(str));
	if (!*val)
	{
		free(*name);
		return (1);
	}
	return (0);
}
