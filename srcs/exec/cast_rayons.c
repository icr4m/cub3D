/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:14:50 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/05 18:42:52 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	cal_horizontal_inter(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	step_x;
	float	step_y;
	int		orientation;

	step_x = TILE_SIZE / tan(angle);
	step_y = TILE_SIZE;
	h_y = floor(data->player->co.co_y / TILE_SIZE) * TILE_SIZE;
	orientation = inter_check(angle, &h_y, &step_y, 1);
	h_x = data->player->co.co_x + (h_y - data->player->co.co_y) / tan(angle);
	if ((unit_circle(angle, 'y') && step_x > 0) || (!unit_circle(angle, 'y')
			&& step_x < 0))
		step_x *= -1;
	while (no_wall_hit(data, h_x, h_y - orientation))
	{
		h_x += step_x;
		h_y += step_y;
	}
	// if (no_wall_hit(data, h_x, h_y - orientation) == 0)
	// {
	// 	data->ray->wall_hit_x = h_x;
	// 	data->ray->wall_hit_y = h_y;
	// }
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}

float	cal_vertical_inter(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	step_x;
	float	step_y;
	int		orientation;

	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(angle);
	h_x = floor(data->player->co.co_x / TILE_SIZE) * TILE_SIZE;
	orientation = inter_check(angle, &h_x, &step_x, 0);
	h_y = data->player->co.co_y + (h_x - data->player->co.co_x) * tan(angle);
	if ((unit_circle(angle, 'x') && step_y < 0) || (!unit_circle(angle, 'x')
			&& step_y > 0))
		step_y *= -1;
	while (no_wall_hit(data, h_x - orientation, h_y))
	{
		h_x += step_x;
		h_y += step_y;
	}
	// if (no_wall_hit(data, h_x, h_y - orientation) == 0)
	// {
	// 	data->ray->wall_hit_x = h_x;
	// 	data->ray->wall_hit_y = h_y;
	// }
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}

void	cast_rayons(t_data *data)
{
	double	inter_ve;
	double	inter_ho;
	int		ray;

	ray = 0;
	data->ray->angle = data->player->angle - (data->player->fov / 2);
	while (ray < SCREEN_W)
	{
		data->ray->inter_h = 0;
		data->ray->is_door = 0;
		inter_ho = cal_horizontal_inter(data, nor_angle(data->ray->angle));
		inter_ve = cal_vertical_inter(data, nor_angle(data->ray->angle));
		if (inter_ve <= inter_ho)
			data->ray->distance = inter_ve;
		else
		{
			data->ray->distance = inter_ho;
			data->ray->inter_h = 1;
		}
		ray++;
		data->ray->angle += (data->player->fov / SCREEN_W);
		render_wall(data, ray);
	}
}
