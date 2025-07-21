/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 variables.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/06 12:03:08 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/06 12:15:37 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static int	_split_assignment(char *str, t_sh_var **env);
static bool	_is_valid_var_name(char *str);

/** @brief print the shell variables
 *	Print the environment variables in the format name=value
 *	for debugging purposes
 * */
void	print_vars(t_envs *envs, bool only_envs)
{
	t_list		*tmp;
	t_sh_var	*env;

	tmp = envs;
	while (tmp)
	{
		env = tmp->content;
		if (only_envs && env->exported)
			printf("%s=%s\n", env->name, env->value);
		else if (!only_envs)
			printf("%s=%s\n", env->name, env->value);
		tmp = tmp->next;
	}
}

/** @brief parse the variable assignment
 *
 * Parse the variable assignment into a t_env struct.
 * @param str The string to parse in the form key=value
 * @return t_env struct or NULL if there is an error:
 * - allocation error
 * - invalid variable name
 * - invalid variable assignment
 * */
t_sh_var	*parse_variable_assignment(char *str)
{
	t_sh_var	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(t_sh_var));
	if (!res)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	res->name = NULL;
	res->value = NULL;
	if (!ft_strchr(str, '='))
	{
		free_sh_var(res);
		print_shell_error("Invalid variable assignment");
		return (NULL);
	}
	if (_split_assignment(str, &res) != 0)
		return (free_sh_var(res));
	if (!_is_valid_var_name(res->name))
	{
		print_shell_error("Invalid variable name");
		return (free_sh_var(res));
	}
	return (res);
}

/** @brief split the assignment
 * The function splits the assignment string into key and value
 *
 * @param str The string to split
 * @param env The t_env struct.
 *
 * @return 0 on success and 1 on failure.
 * @note Can fail only if an allocation error occurs.
 *
 * */
static int	_split_assignment(char *str, t_sh_var **env)
{
	int		eq_idx;
	char	*key;
	char	*value;

	eq_idx = ft_strchr(str, '=') - str;
	key = ft_substr(str, 0, eq_idx);
	if (!key)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		return (1);
	}
	value = ft_substr(str, eq_idx + 1, ft_strlen(str));
	if (!value)
	{
		free(key);
		print_shell_error(MALLOC_ERROR_MSG);
		return (1);
	}
	(*env)->name = key;
	(*env)->value = value;
	(*env)->exported = false;
	return (0);
}

/** @brief check if the variable name is valid
 *
 * Check if the variable name is valid
 *
 * @param str The string to check
 * @note The variable name must be a valid identifier.
 * 		 In order to be valid, the variable name must start with an
 * 		 alpha character or an underscore, and can only contain
 * 		 alphanumeric characters or underscores.
 * */
static bool	_is_valid_var_name(char *str)
{
	char	*ptr;

	ptr = str;
	if (!*ptr || (!ft_isalpha(*ptr) && *ptr != '_'))
		return (false);
	ptr++;
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (false);
		ptr++;
	}
	return (true);
}
