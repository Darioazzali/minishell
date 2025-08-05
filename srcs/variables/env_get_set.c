/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:59:05 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/05 11:06:39 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_sh_var	*set_new_shell_var(char *name, char *value);

/**
* @brief Returns the environment variable with the given key.
*
* Given the key return a pointer to the struct of the variable.
* @return A pointer to the environment variable with the given name
*         or NULL if does not exits.
*/
t_sh_var	*get_shell_var(t_envs *envs, char *name)
{
	t_list		*tmp;
	t_sh_var	*env;
	size_t		len;

	tmp = envs;
	len = ft_strlen(name);
	while (tmp)
	{
		env = tmp->content;
		if (len == ft_strlen(env->name)
			&& ft_strncmp(env->name, name, ft_strlen(name)) == 0)
			return (env);
		tmp = tmp->next;
	}
	return (NULL);
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
	t_sh_var	*existing;
	t_sh_var	*new;
	t_list		*node;
	char		*new_value;

	existing = get_shell_var(envs, name);
	if (existing)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (1);
		free(existing->value);
		existing->value = new_value;
		return (0);
	}
	new = set_new_shell_var(name, value);
	if (!new)
		return (1);
	node = ft_lstnew(new);
	if (!node)
		return (_env_malloc_err(new));
	ft_lstadd_back(&envs, node);
	return (0);
}

/** @brief get shell var VALUE
 * Get the Value of the shell variable with the given name.
 * If the variable is not found, return NULL.
 * @return A pointer to the value of the shell variable
 * @note The function returns a pointer to the value of the shell variable
 *       and does not allocate memory for it.
 *
 * */
char	*get_shell_var_value(t_envs *envs, char *name)
{
	t_list		*tmp;
	t_sh_var	*env;

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

/**
* @brief Promote the shell variable to environment variable
*
*/
void	promote_var_to_env(t_envs *envs, char *name)
{
	t_list		*tmp;
	t_sh_var	*env;
	size_t		len;

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

/** @brief set new shell var
 *
 * Create a new t_env struct with the given name and value.
 * */

static t_sh_var	*set_new_shell_var(char *name, char *value)
{
	t_sh_var	*new;

	new = malloc(sizeof(t_sh_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		_env_malloc_err(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		_env_malloc_err(new);
		return (NULL);
	}
	new->exported = false;
	return (new);
}
