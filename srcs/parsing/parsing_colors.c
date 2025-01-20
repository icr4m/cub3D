/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:23:40 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 14:49:53 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_colors(t_data *data, t_texture *current)
{
	char	**rgb_splitted;
	char	*line_without_space;
	t_rgb	*rgb;

	rgb = init_rgb_struct(data, current->identifier);
	line_without_space = remove_spaces(data, current->path);
	rgb_splitted = ft_split(line_without_space, ',');
	if (!rgb_splitted)
		handle_malloc_error("parse colors", data);
	check_rgb_values(rgb_splitted, data);
	set_rgb_values(rgb, rgb_splitted, data);
	gc_free(line_without_space);
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
