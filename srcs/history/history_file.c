/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 history_file.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aluque-v <aluque-v@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/20 08:59:40 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/22 13:23:40 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line_from_file(t_history *hist, char *line);
static void	set_last_saved(t_history *hist);

/** @brief Load history from file
 * Load history from file and add it to the history list
 *
 * @param hist history structure
 *
 * @note Can fail if open fails
 * */
void	load_history_from_file(t_history *hist)
{
	int		fd;
	char	*line;

	if (!hist)
		return ;
	if (access(HISTORY_FILE, F_OK) != 0)
		return ;
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening history file"));
	line = get_next_line(fd);
	while ((line) != NULL)
	{
		if (!process_line_from_file(hist, line))
		{
			ft_lstclear(&hist->head, free);
			close(fd);
			return (free(line));
		}
		free(line);
		line = get_next_line(fd);
	}
	set_last_saved(hist);
	close(fd);
}

static int	process_line_from_file(t_history *hist, char *line)
{
	char	*new_line;
	size_t	len;
	t_list	*node;

	if (is_empty_line(line))
		return (1);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		new_line = ft_substr(line, 0, len - 1);
	else
		new_line = ft_strdup(line);
	if (!new_line)
		print_shell_error_ret_int(MALLOC_ERROR_MSG, 0);
	add_history(new_line);
	node = ft_lstnew(new_line);
	if (!node)
	{
		free(new_line);
		print_shell_error_ret_int(MALLOC_ERROR_MSG, 0);
	}
	ft_lstadd_or_assign(&hist->head, node);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	set_last_saved(t_history *hist)
{
	if (ft_lstlast(hist->head))
		hist->last_saved = ft_lstlast(hist->head);
	else
		hist->last_saved = NULL;
}
