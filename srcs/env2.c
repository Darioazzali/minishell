/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:59:05 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/16 15:03:49 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief Set the env variable exported.
 * */
void	set_env_from_shell_var(t_envs *envs, char *name)
{
	t_list	*tmp;
	t_env	*env;

	tmp = envs;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
		{
			env->exported = true;
			return ;
		}
		tmp = tmp->next;
	}
}

/**
* @brief Returns the environment variable with the given name.
*
* Return a pointer to the environment variable with the given name.
* @return A pointer to the environment variable with the given name
*         or NULL if does not exits.
*/
t_env	*get_shell_var(t_envs *envs, char *name)
{
	t_list	*tmp;
	t_env	*env;
	size_t	len;

	tmp = envs;
	len = ft_strlen(name);
	while (tmp)
	{
		env = tmp->content;
		if (len == ft_strlen(env->name)
			&& ft_strncmp(env->name, name, ft_strlen(name)) == 0)
		{
			return (env);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
* @brief Promote the shell variable to environment variable
*
*/
void	promote_var_to_env(t_envs *envs, char *name)
{
	t_list	*tmp;
	t_env	*env;
	size_t	len;

	tmp = envs;
	len = ft_strlen(name);
	while (tmp)
	{
		env = tmp->content;
		if (len == ft_strlen(env->name)
			&& ft_strncmp(env->name, name, len) == 0)
		{
			env->exported = true;
			return ;
		}
		tmp = tmp->next;
	}
}

/** @brief print the shell variables
 *	Print the environment variables in the format name=value
 *	for debugging purposes
 * */
void	print_vars(t_envs *envs, bool only_envs)
{
	t_list	*tmp;
	t_env	*env;

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

/** @brief get shell var VALUE
 * Get the Value of the shell variable with the given name.
 * If the variable is not found, return NULL.
 *
 * */
char	*get_shell_var_value(t_envs *envs, char *name)
{
	t_list	*tmp;
	t_env	*env;

	tmp = envs;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
