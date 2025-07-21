/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluque-v <aluque-v@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:59:40 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/21 07:07:46 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line_from_file(t_history *hist, char *line);
static int	resize_for_file_load(t_history *hist);

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
	{
		perror("Error opening history file");
		return ;
	}
	line = get_next_line(fd);
	while ((line) != NULL)
	{
		if (!process_line_from_file(hist, line))
		{
			close(fd);
			return (free(line));
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	process_line_from_file(t_history *hist, char *line)
{
	char	*new_line;
	size_t	len;

	if (is_empty_line(line))
		return (1);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		new_line = ft_substr(line, 0, len - 1);
	else
		new_line = ft_strdup(line);
	add_history(new_line);
	if (hist->count >= hist->capacity)
	{
		if (!resize_for_file_load(hist))
			return (0);
	}
	hist->commands[hist->count] = ft_strdup(new_line);
	if (hist->commands[hist->count])
		hist->count++;
	free(new_line);
	return (1);
}

static int	resize_for_file_load(t_history *hist)
{
	char	**tmp;

	if (hist->capacity == 0)
		hist->capacity = INITIAL_CAPACITY;
	else
		hist->capacity = hist->capacity * 2;
	tmp = ft_realloc(hist->commands, hist->capacity * sizeof(char *));
	if (!tmp)
		return (0);
	hist->commands = tmp;
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
