/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:14:50 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/11 16:19:38 by ijaber           ###   ########.fr       */
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

static void	init_ray_data(t_data *data, int *ray)
{
	*ray = 0;
	data->ray->angle = data->player->angle - (data->player->fov / 2);
}

static void	set_wall_data_vertical(t_data *data, double dist_v, float wall_x,
		float wall_y)
{
	data->ray->distance = dist_v;
	data->ray->wall_hit_x = wall_x;
	data->ray->wall_hit_y = wall_y;
	data->ray->inter_h = 0;
}

static void	set_wall_data_horizontal(t_data *data, double dist_h, float wall_x,
		float wall_y)
{
	data->ray->distance = dist_h;
	data->ray->wall_hit_x = wall_x;
	data->ray->wall_hit_y = wall_y;
	data->ray->inter_h = 1;
}

static double	handle_intersections(t_data *data, int is_horizontal,
		float *wall_x, float *wall_y)
{
	double	dist;

	data->ray->is_door = 0;
	if (is_horizontal)
		dist = cal_horizontal_inter(data, nor_angle(data->ray->angle));
	else
		dist = cal_vertical_inter(data, nor_angle(data->ray->angle));
	*wall_x = data->ray->wall_hit_x;
	*wall_y = data->ray->wall_hit_y;
	return (dist);
}

void	cast_rayons(t_data *data)
{
	int		ray;
	float	coords[4];
	double	dist[2];
	int		door;

	init_ray_data(data, &ray);
	while (ray < SCREEN_W)
	{
		dist[0] = handle_intersections(data, 1, &coords[0], &coords[1]);
		door = data->ray->is_door;
		dist[1] = handle_intersections(data, 0, &coords[2], &coords[3]);
		if (dist[1] <= dist[0])
			set_wall_data_vertical(data, dist[1], coords[2], coords[3]);
		else
			set_wall_data_horizontal(data, dist[0], coords[0], coords[1]);
		if (dist[1] > dist[0])
			data->ray->is_door = door;
		render_wall(data, ray);
		cast_curseur(data);
		data->ray->angle += (data->player->fov / SCREEN_W);
		ray++;
	}
}
