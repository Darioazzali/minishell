/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:00:25 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/02 10:33:09 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	_export(t_envs *envs, char *name, char *value)
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
