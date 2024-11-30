/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:32:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 07:02:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls(t_data *data)
{
	const size_t	nb_line = data->amount_l - data->l_map_start;
	size_t			i;

	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[0][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[nb_line][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
	i = 0;
	while (i < nb_line)
	{
		if (data->map_2d[i][0] != 1 || data->map_2d[i][data->amount_c - 1] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
}

void	check_player(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (i < data->amount_l - data->l_map_start)
	{
		j = 0;
		while (j < data->amount_c)
		{
			if (data->map_2d[i][j] == 11 || data->map_2d[i][j] == 12
				|| data->map_2d[i][j] == 13 || data->map_2d[i][j] == 14)
				count++;
			j++;
		}
		i++;
	}
	if (count < 1)
		free_and_exit(EXIT_FAILURE, NO_P_ERR);
	if (count > 1)
		free_and_exit(EXIT_FAILURE, TOO_P_ERR);
}

void	parse_colors(t_data *data, t_texture *current)
{
	char	**rgb_splitted;
	char	*line_without_space;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	if (ft_strcmp(current->identifier, ID_C) == 0 && !data->ceiling)
		data->ceiling = gc_malloc(sizeof(t_rgb));
	if (ft_strcmp(current->identifier, ID_F) == 0 && !data->floor)
		data->floor = gc_malloc(sizeof(t_rgb));
	if ((ft_strcmp(current->identifier, ID_C) == 0 && !data->ceiling)
		|| (ft_strcmp(current->identifier, ID_F) == 0 && !data->floor))
		handle_malloc_error("parse colors", data);
	line_without_space = gc_malloc(ft_strlen(current->path) + 1);
	if (!line_without_space)
		handle_malloc_error("parse colors", data);
	while (*current->path)
	{
		if (*current->path != ' ')
			line_without_space[i++] = *current->path;
		current->path++;
	}
	line_without_space[i] = '\0';
	rgb_splitted = ft_split(line_without_space, ',');
	if (!rgb_splitted)
		handle_malloc_error("parse colors", data);
	if (!rgb_splitted[0] || !rgb_splitted[1] || !rgb_splitted[2])
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR);
	r = ft_atoi(rgb_splitted[0]);
	g = ft_atoi(rgb_splitted[1]);
	b = ft_atoi(rgb_splitted[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || !r || !g
		|| !b)
		free_and_exit(EXIT_FAILURE, RGB_ERR);
	gc_free(line_without_space);
	if (ft_strcmp(current->identifier, ID_C) == 0)
	{
		data->ceiling->r = r;
		data->ceiling->g = g;
		data->ceiling->b = b;
	}
	if (ft_strcmp(current->identifier, ID_F) == 0)
	{
		data->floor->r = r;
		data->floor->g = g;
		data->floor->b = b;
	}
	gc_free_2d(rgb_splitted);
}

void	check_color(t_data *data)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (ft_strcmp(current->identifier, ID_C) == 0
			|| ft_strcmp(current->identifier, ID_F) == 0)
			parse_colors(data, current);
		current = current->next;
	}
}
