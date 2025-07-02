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

t_env	*parse_env(char *str);

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
		tmp = parse_env(*ptr);
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

t_env	*parse_env(char *str)
{
	t_env	*env;
	char	**tmp;

	env = malloc(sizeof(t_env));
	tmp = ft_split(str, '=');
	env->name = tmp[0];
	env->value = tmp[1];
	env->exported = true;
	free(tmp);
	return (env);
}

void	print_shell_vars(t_envs *envs)
{
	t_list	*tmp;
	t_env	*env;

	tmp = envs;
	printf("envs %p\n", envs);
	while (tmp)
	{
		env = tmp->content;
		printf("%s=%s\n", env->name, env->value);
		tmp = tmp->next;
	}
}

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

int	set_shell_var(t_envs *envs, char *name, char *value)
{
	char	*tmp;
	t_env	*new;
	t_list	*node;

	tmp = get_shell_var_value(envs, name);
	if (tmp)
	{
		tmp = value;
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->name = name;
	new->value = value;
	node = ft_lstnew(new);
	if (!node)
		return (1);
	ft_lstadd_back(&envs, node);
	return (0);
}
