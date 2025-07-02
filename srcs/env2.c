/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:59:05 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/02 10:19:39 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

	tmp = envs;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
			return (env);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
* @brief Promote the shell variable to environment variable
*/
void	promote_var_to_env(t_envs *envs, char *name)
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
