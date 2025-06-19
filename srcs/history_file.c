#include "minishell.h"

static char	*read_line_from_fd(int fd);
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
	while ((line = read_line_from_fd(fd)) != NULL)
	{
		if (!process_line_from_file(hist, line))
		{
			free(line);
			close(fd);
			return ;
		}
		free(line);
	}
	close(fd);
}

static int	process_line_from_file(t_history *hist, char *line)
{
	if (is_empty_line(line))
		return (1);
	add_history(line);
	if (hist->count >= hist->capacity)
	{
		if (!resize_for_file_load(hist))
			return (0);
	}
	hist->commands[hist->count] = ft_strdup(line);
	if (hist->commands[hist->count])
		hist->count++;
	return (1);
}

static int	resize_for_file_load(t_history *hist)
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

static char	*read_line_from_fd(int fd)
{
	char	*line;
	char	buffer;
	int		len;
	int		capacity;

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
			if (!expand_buffer(&line, &capacity))
				return (NULL);
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

int	is_empty_line(char *line)
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
