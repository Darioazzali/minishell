/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:27:12 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/05 12:28:01 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wait_child_processes(t_ctx *ctx, pid_t *pids, size_t count)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i++], &status, 0);
	}
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		ctx->exit_status = 128 + WTERMSIG(status);
}
