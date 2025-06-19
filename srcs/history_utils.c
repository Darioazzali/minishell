#include "minishell.h"

static int	is_duplicate_command(t_history *hist, char *line)
{
	if (hist->count > 0 && hist->commands[hist->count - 1])
	{
		if (!ft_strncmp(hist->commands[hist->count - 1], line, 
			ft_strlen(line)))
			return (1);
	}
	return (0);
}

static int	resize_history_array(t_history *hist)
{
	char **tmp;

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

void	add_to_history_struct(char *line, t_history *hist)
{
	if (!line || !hist || is_empty_line(line))
		return ;
	if (is_duplicate_command(hist, line))
		return ;
	add_history(line);
	if (hist->count >= hist->capacity)
	{
		if (!resize_history_array(hist))
			return ;
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

int	expand_buffer(char **line, int *capacity)
{
	char *tmp;

	*capacity = *capacity * 2;
	tmp = ft_realloc(*line, *capacity + 1);
	if (!tmp)
	{
		free(*line);
		return (0);
	}
	*line = tmp;
	return (1);
}

