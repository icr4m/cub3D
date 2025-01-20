/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_offset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:19:52 by erwfonta          #+#    #+#             */
/*   Updated: 2025/01/20 17:32:35 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_door_hit_offset(t_data *data)
{
	if (data->ray->inter_h == 1)
		return (data->ray->wall_hit_x);
	return (data->ray->wall_hit_y);
}

static double	get_door_offset(t_data *data, t_texture *texture)
{
	double	hit_pos;

	hit_pos = get_door_hit_offset(data);
	return (fmod(hit_pos, TILE_SIZE) * (texture->s_x / TILE_SIZE));
}

static double	get_horizontal_wall_offset(t_data *data, t_texture *texture)
{
	double	hit_pos;
	double	scale;

	hit_pos = data->ray->wall_hit_x;
	scale = texture->s_x / TILE_SIZE;
	if (data->ray->angle > 0 && data->ray->angle < M_PI)
		return ((TILE_SIZE - fmod(hit_pos, TILE_SIZE)) * scale);
	return (fmod(hit_pos, TILE_SIZE) * scale);
}

static double	get_vertical_wall_offset(t_data *data, t_texture *texture)
{
	double	hit_pos;
	double	scale;

	hit_pos = data->ray->wall_hit_y;
	scale = texture->s_x / TILE_SIZE;
	if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * M_PI / 2)
		return ((TILE_SIZE - fmod(hit_pos, TILE_SIZE)) * scale);
	return (fmod(hit_pos, TILE_SIZE) * scale);
}

double	get_texture_x_offset(t_texture *texture, t_data *data)
{
	if (data->ray->is_door)
		return (get_door_offset(data, texture));
	if (data->ray->inter_h == 1)
		return (get_horizontal_wall_offset(data, texture));
	return (get_vertical_wall_offset(data, texture));
}
