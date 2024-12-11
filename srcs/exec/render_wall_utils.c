/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 03:48:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/10 22:49:58 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
		dst = data->img->addr + (y * data->img->line_length + x
				* (data->img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_texture	*search_texture(t_data *data, char *identifier)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (ft_strcmp(identifier, current->identifier) == 0)
			return (current);
		current = current->next;
	}
	return (current);
}

t_texture	*get_texture(t_data *data, int i)
{
	t_texture	*selected;
	float		angle;

	angle = data->ray->angle;
	// S'assurer que l'angle est bien entre 0 et 2π
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	if (i == 0) // Intersections verticales
	{
		if (angle > M_PI / 2 && angle < 3 * (M_PI / 2))
			selected = search_texture(data, ID_WE);
		else
			selected = search_texture(data, ID_EA);
	}
	else // Intersections horizontales
	{
		if (angle > 0 && angle < M_PI)
			selected = search_texture(data, ID_NO);
		else
			selected = search_texture(data, ID_SO);
	}
	return (selected);
}
