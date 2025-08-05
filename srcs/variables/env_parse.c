/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env_parse.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/17 08:25:51 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/28 08:01:52 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static t_sh_var	*parse_env_str(char *str);
static char		*_sh_var_to_str(t_sh_var *env);

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
			free_sh_var(tmp);
			return (free_envs(envs));
		}
		ft_lstadd_back(&envs, node);
		ptr++;
	}
	return (envs);
}

char	**envs_to_strarr(t_envs *envs)
{
	char	**array;
	int		i;

	if (!envs)
		return (NULL);
	i = 0;
	array = ft_calloc(ft_lstsize(envs) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (envs)
	{
		array[i] = _sh_var_to_str(envs->content);
		if (!array[i])
		{
			print_shell_error(MALLOC_ERROR_MSG);
			return (clean_str_array(array, i));
		}
		envs = envs->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static char	*_sh_var_to_str(t_sh_var *env)
{
	size_t	len_name;
	size_t	len_value;
	size_t	len;
	char	*ret;

	len_name = ft_strlen(env->name);
	len_value = ft_strlen(env->value);
	len = len_name + 1 + len_value + 1;
	ret = malloc(len * sizeof(char));
	if (!ret)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	ft_strlcpy(ret, env->name, len);
	ft_strlcat(ret, "=", len);
	ft_strlcat(ret, env->value, len);
	return (ret);
}

/** @brief parse the env string
 * Parse the environment variable string into a t_env struct.
 * */
static t_sh_var	*parse_env_str(char *str)
{
	t_sh_var	*env;
	char		*first_eq;

	env = malloc(sizeof(t_sh_var));
	if (!env)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	first_eq = ft_strchr(str, '=');
	if (!first_eq)
		return (print_shell_error_ret_null("Invalid env var\n"));
	env->name = ft_substr(str, 0, first_eq - str);
	if (!env->name)
		return (free_sh_var(env), print_shell_error_ret_null(MALLOC_ERROR_MSG));
	if (*(first_eq + 1))
		env->value = ft_substr(str, first_eq - str + 1,
				ft_strlen(str) - ft_strlen(env->name) - 1);
	else
		env->value = ft_strdup("");
	env->exported = true;
	if (!env->name || !env->value)
	{
		free_sh_var(env);
		env = NULL;
	}
	return (env);
}
