/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/01 13:59:04 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/01 14:00:38 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"
#include "log.h"

static t_env	*parse_env_str(char *str);
static int		_env_mem_err(t_env *env);
static t_env	*set_new_shell_var(char *name, char *value);

/** @brief parse the envs string.
 *	Parse the environment variables string into a t_envs list.
 * */
t_envs	*parse_envs(char **str)
{
	char	**ptr;
	t_envs	*envs;
	t_env	*tmp;
	t_list	*node;

	ptr = str;
	envs = NULL;
	while (*ptr)
	{
		tmp = parse_env_str(*ptr);
		if (!tmp)
		{
			free(envs);
			return (NULL);
		}
		node = ft_lstnew(tmp);
		ft_lstadd_back(&envs, node);
		ptr++;
	}
	return (envs);
}

/** @brief parse the env string
 * Parse the environment variable string into a t_env struct.
 * */
static t_env	*parse_env_str(char *str)
{
	t_env	*env;
	char	**tmp;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		return (NULL);
	}
	tmp = ft_split(str, '=');
	if (!tmp)
	{
		_env_mem_err(env);
		return (NULL);
	}
	env->name = tmp[0];
	env->value = tmp[1];
	env->exported = true;
	free(tmp);
	return (env);
}

/** 
 * @brief set shell var
 *
 * Set the value of the shell variable with the given name to the given value.
 * If the variable already exists, its value is updated.
 * @return 0 on success
 * */
int	set_shell_var(t_envs *envs, char *name, char *value)
{
	t_env	*existing;
	t_env	*new;
	t_list	*node;
	char	*new_value;

	existing = get_shell_var(envs, name);
	if (existing)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (1);
		free(existing->value);
		existing->value = value;
		return (0);
	}
	new = set_new_shell_var(name, value);
	if (!new)
	{
		return (1);
	}
	node = ft_lstnew(new);
	if (!node)
		return (_env_mem_err(new));
	ft_lstadd_back(&envs, node);
	return (0);
}

static t_env	*set_new_shell_var(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		_env_mem_err(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		_env_mem_err(new);
		return (NULL);
	}
	return (new);
}

static int	_env_mem_err(t_env *env)
{
	print_error(MALLOC_ERROR_MSG);
	free_env(env);
	return (1);
}
