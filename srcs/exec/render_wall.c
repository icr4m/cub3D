/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 11:36:03 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_plafond_sol(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_H)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->ceiling->r,
				data->ceiling->g, data->ceiling->b));
	i = 0;
	while (i < top_pix)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->floor->r,
				data->floor->g, data->floor->b));
}

int	get_color(t_data *data, int flag)
{
	data->ray->angle = nor_angle(data->ray->angle);
	if (flag == 0)
	{
		if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xFF0000FF); // east wall
	}
	if (data->ray->is_door == 1)
		return (0xAAA32AFF);
	else
	{
		if (data->ray->angle > 0 && data->ray->angle < M_PI)
			return (0x0000FFFF); // south wall
		else
			return (0xFFFF00FF); // north wall
	}
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	color;

	color = get_color(data, data->ray->inter_h);
	while (top_pix < bot_pix)
	{
		my_mlx_pixel_put(data, ray, top_pix, color);
		top_pix++;
	}
}

void	render_wall(t_data *data, int ray)
{
	double	wall_h;
	double	top_pix;
	double	bot_pix;

	data->ray->distance *= cos(nor_angle(data->ray->angle
				- data->player->angle));
	wall_h = (TILE_SIZE / data->ray->distance) * ((SCREEN_W / 2)
			/ tan(data->player->fov / 2));
	bot_pix = (SCREEN_H / 2) + (wall_h / 2);
	top_pix = (SCREEN_H / 2) - (wall_h / 2);
	if (bot_pix > SCREEN_H)
		bot_pix = SCREEN_H;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(data, ray, top_pix, bot_pix);
	draw_plafond_sol(data, ray, top_pix, bot_pix);
}
