/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 unset.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/04 15:13:13 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/16 11:26:46 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static t_list	*_find_var_node(char *key, t_envs *envs);
static void		_free_env_lst(void *content);

/** @brief unset the given keys from the environment
 *
 * Remove the environment variables with the given keys from the environment list
 * 
 * @param envs The environment list
 * @param keys The keys to unset
 * */
int	unset_btin(t_envs **envs, char **keys)
{
	char	**ptr;

	if (!keys)
		return (0);
	ptr = keys;
	while (*ptr)
	{
		remove_shell_var(envs, *ptr);
		ptr++;
	}
	return (0);
}

/** @brief Remove a variable from the environment
 * 
 * Remove the shell variable with the given key from the environment list
 * @param envs The environment list
 * @param key The key of the variable to unset
 * */
void	remove_shell_var(t_envs **envs, char *key)
{
	t_list	*found;

	if (!envs || !*envs || !key)
		return ;
	found = _find_var_node(key, *envs);
	if (!found)
		return ;
	ft_lstremove_node(envs, found, _free_env_lst);
}

/** @brief Find a variable node by its key
 *	
 *  Find a node in the list of environment variables that corresponds to the key.
 *
 * @param key The key of the variable to find
 * @param envs The environment list
 *
 * @return A pointer to the node if found, NULL otherwise
 * */
static t_list	*_find_var_node(char *key, t_envs *envs)
{
	t_list		*tmp;
	t_sh_var	*env;
	size_t		len;

	tmp = envs;
	len = ft_strlen(key);
	while (tmp)
	{
		env = tmp->content;
		if (ft_strlen(env->name) == len
			&& !ft_strncmp(env->name, key, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/** @brief Free the environment list
 *  
 *  Free the environment node and its content.
 * */
static void	_free_env_lst(void *content)
{
	t_sh_var	*env;

	env = content;
	free_sh_var(env);
}
