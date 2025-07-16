/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 env3.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/16 15:34:02 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/16 15:36:40 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static void	free_env_node(void *content);

void	*free_envs(t_envs *envs)
{
	ft_lstclear(&envs, free_env_node);
	return (NULL);
}

static void	free_env_node(void *content)
{
	free_env((t_env *)content);
}

void	free_split_result(char **split_result)
{
	int	i;

	if (!split_result)
		return ;
	i = 0;
	while (split_result[i])
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}
