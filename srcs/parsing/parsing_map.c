/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:22 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 02:56:17 by rsk              ###   ########.fr       */
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
			free_and_exit(EXIT_FAILURE, "Unknown character in the map", data);
		}
	}
}

static void	init_line(t_data *data, int i)
{
	size_t	j;

	data->map_2d[i] = gc_malloc(data->amount_c * (sizeof(int)));
	if (!data->map_2d[i])
		handle_malloc_error("parse 2d map", data);
	j = 0;
	while (j < data->amount_c)
	{
		data->map_2d[i][j] = -42;
		j++;
	}
}

static void	allocate_line(char *line, t_data *data, int i)
{
	size_t	index;

	init_line(data, i);
	index = 0;
	while (line[index] && index < data->amount_c)
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
			data->map_2d[i][index] = -42;
		index++;
	}
}

void	create_2dmap(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		unknown_char(line, data);
		allocate_line(line, data, i);
		gc_free(line);
		line = get_next_line(data->fd);
		i++;
		if (line)
			if (ft_strcmp(line, "\n"))
				data->amount_l_map++;
	}
}

void	parse_map(t_data *data, char **av)
{
	const size_t	nb_line = data->amount_l - data->l_map_start;
	size_t			follow_l;
	char			*line;

	follow_l = data->l_map_start - 1;
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, ERR_OPEN, data);
	data->map_2d = gc_malloc((nb_line + 1) * (sizeof(int *)));
	if (!data->map_2d)
		handle_malloc_error("parse 2d map", data);
	while (follow_l)
	{
		line = get_next_line(data->fd);
		gc_free(line);
		follow_l--;
	}
	create_2dmap(data);
	close(data->fd);
}
