/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluque-v <aluque-v@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:43:38 by aluque-v          #+#    #+#             */
/*   Updated: 2025/06/19 12:43:45 by aluque-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
static int	is_empty_line(char *line);
static char	*read_line_from_fd(int fd);
static void	load_history_from_file(t_history *hist);

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
		if (hist->commands[i])
		{
			write(fd, hist->commands[i], ft_strlen(hist->commands[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	close (fd);
}

void	add_to_history_struct(char *line, t_history *hist)
{
	char	*tmp;

	if (!line || !hist || is_empty_line(line))
		return ;
	if (hist->count > 0 && hist->commands[hist->count - 1])
	{
		if (!ft_strncmp(hist->commands[hist->count - 1], line, ft_strlen(line)))
			return ;
	}
	add_history(line);
	if (hist->count >= hist->capacity)
	{
		if(hist->capacity == 0)
		{
			hist->capacity = INITIAL_CAPACITY;
		}
		else
			hist->capacity = hist->capacity * 2;
		tmp = ft_realloc(hist->commands, hist->capacity * sizeof(char *));
		if (!tmp)
			return ;
		hist->commands = (char **)tmp;
	}
	hist->commands[hist->count] = ft_strdup(line);
	if (hist->commands[hist->count])
		hist->count++;
}

void	free_history_struct(t_history *hist)
{
	int	i;

	if (!hist)
		return ;
	if (hist->commands)
	{
		i = 0;
		while (i < hist->count)
		{
			if (hist->commands[i])
				free(hist->commands[i]);
			i++;
		}
		free(hist->commands);
	}
}

static void	load_history_from_file(t_history *hist)
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
	while ((line = read_line_from_fd(fd)) != NULL)
	{
		if (!is_empty_line(line))
		{
			add_history(line);
			if (hist->count >= hist->capacity)
			{
				if (hist->capacity == 0)
				{
					hist->capacity = INITIAL_CAPACITY;
				}
				else
					hist->capacity = hist->capacity * 2;
				hist->commands = ft_realloc(hist->commands, hist->capacity * sizeof(char *));
				if (!hist->commands)
				{
					free(line);
					close(fd);
					return ;
				}
			}
			hist->commands[hist->count] = ft_strdup(line);
			if (hist->commands[hist->count])
				hist->count++;
		}
		free(line);
	}
	close(fd);
}

static char	*read_line_from_fd(int fd)
{
	char	*line;
	char	buffer;
	int		len;
	int		capacity;
	char	*tmp;

	len = 0;
	capacity = 64;
	line = malloc(capacity + 1);
	if (!line)
		return (NULL);
	while (read(fd, &buffer, 1) > 0)
	{
		if (buffer == '\n')
			break;
		if (len >= capacity)
		{
			capacity = capacity * 2;
			tmp = ft_realloc(line, capacity + 1);
			if (!tmp)
			{
				free(line);
				return (NULL);
			}
			line = tmp;
		}
		line[len] = buffer;
		len++;
	}
	line[len] = '\0';
	if (len == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	is_empty_line(char *line)
{
	int	i;

	if(!line)
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
