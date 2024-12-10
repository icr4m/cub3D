/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:14:50 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/10 16:56:19 by rsk              ###   ########.fr       */
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
	data->ray->wall_hit_x = h_x;
	data->ray->wall_hit_y = h_y;
	if (no_wall_hit(data, h_x, h_y - orientation) == 0)
	{
		data->ray->wall_hit_x = h_x;
		data->ray->wall_hit_y = h_y;
	}
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
	if (no_wall_hit(data, h_x - orientation, h_y) == 0)
	{
		data->ray->wall_hit_x = h_x;
		data->ray->wall_hit_y = h_y;
	}
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}

// Dans cast_rayons.c:
void	cast_rayons(t_data *data)
{
	double	inter_ve;
	double	inter_ho;
	int		ray;
	int		door_h;
	int		door_v;

	ray = 0;
	data->ray->angle = data->player->angle - (data->player->fov / 2);
	while (ray < SCREEN_W)
	{
		data->ray->is_door = 0;
		door_h = 0;
		door_v = 0;
		data->ray->is_door = 0;
		inter_ho = cal_horizontal_inter(data, nor_angle(data->ray->angle));
		door_h = data->ray->is_door;
		data->ray->is_door = 0;
		inter_ve = cal_vertical_inter(data, nor_angle(data->ray->angle));
		// if (ray == SCREEN_W / 2) // Pour le rayon au centre de l'écran
		// {
		// 	printf("Angle: %f\n", data->ray->angle * 180 / M_PI);
		// 	printf("Horizontal hit: (%f, %f)\n", data->ray->wall_hit_x,
		// 			data->ray->wall_hit_y);
		// 	if (data->ray->inter_h)
		// 	{
		// 		printf("Using horizontal intersection\n");
		// 		printf("Texture: %s\n", data->ray->angle > 0
		// 				&& data->ray->angle < M_PI ? "NO" : "SO");
		// 	}
		// 	else
		// 	{
		// 		printf("Using vertical intersection\n");
		// 		printf("Texture: %s\n", data->ray->angle > M_PI / 2
		// 				&& data->ray->angle < 3 * M_PI / 2 ? "WE" : "EA");
		// 	}
		// }
		door_v = data->ray->is_door;
		if (inter_ve <= inter_ho)
		{
			data->ray->distance = inter_ve;
			data->ray->inter_h = 0;
			data->ray->is_door = door_v;
		}
		else
		{
			data->ray->distance = inter_ho;
			data->ray->inter_h = 1;
			data->ray->is_door = door_h;
		}
		render_wall(data, ray);
		cast_curseur(data);
		data->ray->angle += (data->player->fov / SCREEN_W);
		ray++;
	}
}
