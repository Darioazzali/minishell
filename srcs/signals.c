/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:18:21 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/17 13:02:40 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_sigint(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sig_handler_sigint_in_heredoc(int sig)
{
	printf("\n");
	(void) sig;
	exit(130);
}

void	sig_handler_sigint_in_process(int sig)
{
	printf("\n");
	(void) sig;
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	printf("Quit (core dumped)\n");
}
