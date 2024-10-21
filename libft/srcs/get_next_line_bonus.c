/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:24:54 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/12 16:06:58 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_line_status	get_line_from_buff(char **line, char *buffer)
{
	size_t	index;

	index = index_of(buffer, '\n');
	if (*buffer != '\0')
	{
		*line = strnjoin(*line, buffer, index + 1);
		if (buffer[index] == '\n')
		{
			ft_strncpy(buffer, buffer + index + 1, BUFFER_SIZE);
			return (VALID_LINE);
		}
	}
	return (INVALID_LINE);
}

static t_line_status	fill_line_from_file(char **line, char *rest,
		const int fd)
{
	ssize_t	read_bytes;
	char	buffer[BUFFER_SIZE + 1];

	ft_bzero(buffer, BUFFER_SIZE + 1);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0 && get_line_from_buff(line, buffer) == INVALID_LINE)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (read_bytes == -1)
		return (INVALID_LINE);
	ft_strncpy(rest, buffer, read_bytes);
	return (VALID_LINE);
}

static void	get_line(int fd, char **line)
{
	static char	rest[OPEN_MAX][BUFFER_SIZE + 1] = {0};

	if (get_line_from_buff(line, rest[fd]) == INVALID_LINE)
		fill_line_from_file(line, rest[fd], fd);
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd > -1 && fd < OPEN_MAX && OPEN_MAX > 0 && BUFFER_SIZE <= INT_MAX
		/ OPEN_MAX)
		get_line(fd, &line);
	return (line);
}

// unsigned int	ft_strlcpy(char *dest, char *src, size_t size)
// {
// 	unsigned int	i;
// 	unsigned int	x;

// 	x = ft_strlen(src);
// 	i = 0;
// 	if (size != 0)
// 	{
// 		while (src[i] != '\0' && i < size - 1)
// 		{
// 			dest[i] = src[i];
// 			i++;
// 		}
// 		dest[i] = '\0';
// 	}
// 	return (x);
// }
