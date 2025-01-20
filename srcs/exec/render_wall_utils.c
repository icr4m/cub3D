/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 03:48:01 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 17:28:23 by ijaber           ###   ########.fr       */
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

	if (data->ray->is_door)
		return (search_texture(data, ID_DO));
	angle = data->ray->angle;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	if (i == 0)
	{
		if (angle > M_PI / 2 && angle < 3 * (M_PI / 2))
			selected = search_texture(data, ID_WE);
		else
			selected = search_texture(data, ID_EA);
	}
	else
	{
		if (angle > 0 && angle < M_PI)
			selected = search_texture(data, ID_SO);
		else
			selected = search_texture(data, ID_NO);
	}
	return (selected);
}

void	draw_plafond_sol(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_H)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->floor->r,
				data->floor->g, data->floor->b));
	i = 0;
	while (i < top_pix)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->ceiling->r,
				data->ceiling->g, data->ceiling->b));
}
