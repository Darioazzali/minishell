/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:06:02 by dazzali           #+#    #+#             */
/*   Updated: 2025/02/17 07:51:28 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*clean_buffer(char *buf);
static char	*read_fd(int fd, char *storage);
static char	*join_read_buf(char *buf, char *r_b);
static char	*free_buffer(char **str);

char	*get_next_line(int fd)
{
	static char	*buf = {0};
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((buf && !ft_strchr(buf, '\n')) || !buf)
		buf = read_fd (fd, buf);
	if (!buf)
		return (NULL);
	line = __ft_next_line(buf);
	if (!line)
		return (free_buffer(&buf));
	buf = clean_buffer(buf);
	return (line);
}

static char	*read_fd(int fd, char *buf)
{
	ssize_t	r_bytes;
	char	*read_buf;

	r_bytes = 1;
	read_buf = malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	if (!read_buf)
		return (free_buffer(&buf));
	read_buf[0] = '\0';
	while (r_bytes > 0 && !ft_strchr(read_buf, '\n'))
	{
		r_bytes = read (fd, read_buf, GNL_BUFFER_SIZE);
		if (r_bytes > 0)
		{
			read_buf[r_bytes] = '\0';
			buf = join_read_buf(buf, read_buf);
		}
	}
	free(read_buf);
	if (r_bytes == -1)
		return (free_buffer(&buf));
	return (buf);
}

static char	*free_buffer(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*clean_buffer(char *buf)
{
	char	*tmp;
	char	*line_feed;
	size_t	len;

	line_feed = ft_strchr(buf, '\n');
	if (!line_feed)
	{
		tmp = NULL;
		return (free_buffer(&buf));
	}
	else
		len = (line_feed - buf) + 1;
	if (!buf[len])
		return (free_buffer(&buf));
	tmp = ft_substr(buf, len, ft_strlen(buf) - len);
	free_buffer(&buf);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*join_read_buf(char *buf, char *r_b)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (!buf)
	{
		buf = malloc(sizeof(char) + 1);
		if (!buf)
			return (0);
		buf[0] = 0;
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(buf) + ft_strlen(r_b) + 1);
	if (!str)
		return (free_buffer(&buf));
	i = -1;
	while (buf[++i])
		str[i] = buf[i];
	c = -1;
	while (r_b[++c])
		str[i + c] = r_b[c];
	str[i + c] = '\0';
	free(buf);
	return (str);
}
