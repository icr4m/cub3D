/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:23:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 19:57:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	if (ft_strcmp(rgb_splitted[0], "\n") == 0 || ft_strcmp(rgb_splitted[1],
			"\n") == 0 || ft_strcmp(rgb_splitted[2], "\n") == 0)
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	r = ft_atoi(rgb_splitted[0]);
	g = ft_atoi(rgb_splitted[1]);
	b = ft_atoi(rgb_splitted[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_and_exit(EXIT_FAILURE, RGB_ERR, data);
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
