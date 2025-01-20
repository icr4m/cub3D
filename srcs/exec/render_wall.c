/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 15:22:00 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_texture_color(unsigned char *rgb, int pos, t_texture *texture)
{
	rgb[0] = *(texture->pixel_addr + pos);
	rgb[1] = *(texture->pixel_addr + pos + 1);
	rgb[2] = *(texture->pixel_addr + pos + 2);
}

static int	get_texture_color(int pos, t_texture *texture)
{
	unsigned char	rgb[3];

	if (texture->bpp == 32)
		return (*(unsigned int *)(texture->pixel_addr + pos));
	set_texture_color(rgb, pos, texture);
	return (create_trgb(255, rgb[2], rgb[1], rgb[0]));
}

static int	calculate_pos(double y_offset, double x_offset, t_texture *texture)
{
	return (((int)y_offset * texture->line_lenght) + ((int)x_offset
			* (texture->bpp / 8)));
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix)
{
	t_texture	*texture;
	double		x_offset;
	double		y_offset;
	double		step;
	int			color;

	texture = get_texture(data, data->ray->inter_h);
	if (!texture || !texture->img || !texture->pixel_addr)
		return ;
	step = (double)texture->s_y / data->wall_h;
	x_offset = get_texture_x_offset(texture, data);
	y_offset = (top_pix - (SCREEN_H / 2) + (data->wall_h / 2)) * step;
	if (y_offset < 0)
		y_offset = 0;
	while (top_pix < bot_pix && (int)y_offset < texture->s_y)
	{
		color = get_texture_color(calculate_pos(y_offset, x_offset, texture),
				texture);
		my_mlx_pixel_put(data, ray, top_pix, color);
		y_offset += step;
		top_pix++;
	}
}

void	render_wall(t_data *data, int ray)
{
	double	top_pix;
	double	bot_pix;

	data->ray->distance *= cos(nor_angle(data->ray->angle
				- data->player->angle));
	data->wall_h = (TILE_SIZE / data->ray->distance) * ((SCREEN_W / 2)
			/ tan(data->player->fov / 2));
	bot_pix = (SCREEN_H / 2) + (data->wall_h / 2);
	top_pix = (SCREEN_H / 2) - (data->wall_h / 2);
	if (bot_pix > SCREEN_H)
		bot_pix = SCREEN_H;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(data, ray, top_pix, bot_pix);
	draw_plafond_sol(data, ray, top_pix, bot_pix);
}
