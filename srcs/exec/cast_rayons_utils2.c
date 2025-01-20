/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:31:22 by rsk               #+#    #+#             */
/*   Updated: 2025/01/20 02:34:26 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	data->ray->wall_hit_x = h_x;
	data->ray->wall_hit_y = h_y;
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
	data->ray->wall_hit_x = h_x;
	data->ray->wall_hit_y = h_y;
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}
