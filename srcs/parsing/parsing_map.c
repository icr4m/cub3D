/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:22 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 23:08:03 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	unknown_char(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == WALL || str[i] == FLOOR || str[i] == PLAYER_E
			|| str[i] == PLAYER_N || str[i] == PLAYER_S || str[i] == PLAYER_W
			|| str[i] == DOOR || str[i] == EMPTY || str[i] == ENDOF)
			i++;
		else
		{
			close(data->fd);
			free_and_exit(EXIT_FAILURE, "Unknown character in the map");
		}
	}
}

void	allocate_line(char *line, t_data *data, int i)
{
	int	index;

	index = 0;
	data->map_2d[i] = gc_malloc(ft_strlen(line) * (sizeof(int)));
	if (!data->map_2d[i])
		handle_malloc_error("parse 2d map", data);
	while (line[index] != '\0')
	{
		if (line[index] == FLOOR)
			data->map_2d[i][index] = 0;
		else if (line[index] == WALL)
			data->map_2d[i][index] = 1;
		else if (line[index] == PLAYER_N)
			data->map_2d[i][index] = 11;
		else if (line[index] == PLAYER_S)
			data->map_2d[i][index] = 12;
		else if (line[index] == PLAYER_E)
			data->map_2d[i][index] = 13;
		else if (line[index] == PLAYER_W)
			data->map_2d[i][index] = 14;
		else if (line[index] == DOOR)
			data->map_2d[i][index] = 42;
		else
			data->map_2d[i][index] = -1;
		index++;
	}
}

void	parse_map(t_data *data, char *ex_line)
{
	int				i;
	char			*line;
	const size_t	nb_line = data->amount_l - data->l_map_start;

	line = ex_line;
	i = 0;
	data->map_2d = gc_malloc((nb_line + 1) * (sizeof(int *)));
	if (!data->map_2d)
		handle_malloc_error("parse 2d map", data);
	while (line)
	{
		unknown_char(line, data);
		allocate_line(line, data, i);
		line = get_next_line(data->fd);
		i++;
	}
	close(data->fd);
}
