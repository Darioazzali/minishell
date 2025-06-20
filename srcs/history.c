/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluque-v <aluque-v@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:38 by aluque-v          #+#    #+#             */
/*   Updated: 2025/06/20 09:16:11 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*init_history(void)
{
	t_history	*hist;

	hist = malloc(sizeof(t_history));
	if (!hist)
		return (NULL);
	hist->commands = NULL;
	hist->count = 0;
	hist->capacity = 0;
	load_history_from_file(hist);
	return (hist);
}

static void	write_command_to_file(int fd, char *command)
{
	if (command)
	{
		write(fd, command, ft_strlen(command));
		write(fd, "\n", 1);
	}
}

void	save_to_history_file(t_history *hist)
{
	int	fd;
	int	i;

	if (!hist || !hist->commands)
		return ;
	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating history file");
		return ;
	}
	i = 0;
	while (i < hist->count)
	{
		write_command_to_file(fd, hist->commands[i]);
		i++;
	}
	close (fd);
}
