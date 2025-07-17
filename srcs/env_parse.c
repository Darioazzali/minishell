/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:25:51 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/17 08:58:53 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_sh_var	*parse_env_str(char *str);

/** @brief parse the envs string.
 *	Parse the environment variables string format into a t_envs list.
 *
 *	@param str The string to parse from the **env** variable
 *
 * */
t_envs	*parse_envs(char **str)
{
	char		**ptr;
	t_envs		*envs;
	t_sh_var	*tmp;
	t_list		*node;

	ptr = str;
	envs = NULL;
	while (*ptr)
	{
		tmp = parse_env_str(*ptr);
		if (!tmp)
			return (free_envs(envs));
		node = ft_lstnew(tmp);
		if (!node)
		{
			free_env(tmp);
			return (free_envs(envs));
		}
		ft_lstadd_back(&envs, node);
		ptr++;
	}
	return (envs);
}

/** @brief parse the env string
 * Parse the environment variable string into a t_env struct.
 * */
static t_sh_var	*parse_env_str(char *str)
{
	t_sh_var	*env;
	char		**tmp;

	env = malloc(sizeof(t_sh_var));
	if (!env)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	tmp = ft_split(str, '=');
	if (!tmp)
	{
		_env_malloc_err(env);
		return (NULL);
	}
	env->name = ft_strdup(tmp[0]);
	if (tmp[1])
		env->value = ft_strdup(tmp[1]);
	else
		env->value = ft_strdup("");
	env->exported = true;
	if (!env->name || !env->value)
	{
		free_env(env);
		env = NULL;
	}
	free_split_result(tmp);
	return (env);
}
