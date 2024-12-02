/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/02 03:56:57 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_plafond_sol(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	(void)top_pix;
	while (i < SCREEN_H)
		my_mlx_pixel_put(data, ray, i++, 0xB99470FF);
	i = 0;
	while (i < SCREEN_W)
		my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF);
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix)
{
	while (top_pix < bot_pix)
	{
		my_mlx_pixel_put(data, ray, top_pix, 0xB5B5B5FF);
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
