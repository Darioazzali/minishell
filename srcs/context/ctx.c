/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ctx.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 14:12:00 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 14:13:47 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static	int	_increment_shlvl(t_envs *envs);

int	init_program(t_ctx **ctx, char **env)
{
	t_envs	*envs;

	*ctx = init_ctx();
	if (!*ctx)
		return (0);
	(*ctx)->history = init_history();
	if (!(*ctx)->history)
	{
		perror("Error: Couldn't initialize history\n");
		return (0);
	}
	envs = parse_envs(env);
	if (!envs)
	{
		free_ctx(*ctx);
		return (0);
	}
	_increment_shlvl(envs);
	(*ctx)->envs = envs;
	if (!(*ctx)->envs)
	{
		free_ctx(*ctx);
		return (0);
	}
	return ((*ctx)->ast = NULL, 1);
}

t_ctx	*init_ctx(void)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->pid = getpid();
	ctx->exit_status = 0;
	return (ctx);
}

void	*free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return (NULL);
	if (ctx->history)
		free_history_struct(ctx->history);
	if (ctx->envs)
		free_envs(ctx->envs);
	free(ctx);
	return (NULL);
}

static	int	_increment_shlvl(t_envs *envs)
{
	char	*shlvl_c;
	int		shlvl_nbr;
	char	*ptr;
	char	*res;

	shlvl_c = get_shell_var_value(envs, "SHLVL");
	if (!shlvl_c)
	{
		set_shell_var(envs, "SHLVL", "1");
		return (promote_var_to_env(envs, "SHLVL"), 0);
	}
	ptr = shlvl_c;
	while (*ptr)
	{
		if (!ft_isdigit(*ptr++))
			return (set_shell_var(envs, "SHLVL", "1"), -1);
	}
	shlvl_nbr = (ft_atoi(shlvl_c)) + 1;
	res = ft_itoa(shlvl_nbr);
	if (!res)
		return (-1);
	return (set_shell_var(envs, "SHLVL", res), 0);
}
