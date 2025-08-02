/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluque-v <aluque-v@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:38 by aluque-v          #+#    #+#             */
/*   Updated: 2025/07/22 15:51:41 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @brief Initialize the history
 * Allocate memory for the history struct
 * load history from file
 * @return A pointer to the history struct or NULL if failed
 *
 * @note Can fail if malloc fails
 * */
t_history	*init_history(void)
{
	t_history	*hist;

	hist = malloc(sizeof(t_history));
	if (!hist)
	{
		print_error(MALLOC_ERROR_MSG);
		return (NULL);
	}
	hist->head = NULL;
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

/** @brief Save history to file
 * Save the history to a file from the last saved node
 * update the last saved node
 * 
 * @param hist history structure
 * @note Can fail if open fails or write fails
 * */
void	save_to_history_file(t_history *hist)
{
	int		fd;
	char	*command;
	t_list	*start_node;

	if (!hist)
	{
		print_error("No history\n");
		return ;
	}
	if (hist->last_saved)
		start_node = hist->last_saved->next;
	else
		start_node = hist->head;
	if (!start_node)
		return ;
	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Error creating history file"));
	while (start_node)
	{
		command = start_node->content;
		write_command_to_file(fd, command);
		start_node = start_node->next;
	}
	close (fd);
}
