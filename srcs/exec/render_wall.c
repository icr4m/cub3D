/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/11 12:29:04 by rsk              ###   ########.fr       */
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

double	get_texture_x_offset(t_texture *texture, t_data *data)
{
	double	x_offset;

	if (data->ray->inter_h == 1)
	{
		x_offset = fmod(data->ray->wall_hit_x, TILE_SIZE) * (texture->s_x
				/ TILE_SIZE);
	}
	else
	{
		x_offset = fmod(data->ray->wall_hit_y, TILE_SIZE) * (texture->s_x
				/ TILE_SIZE);
	}
	return (x_offset);
}

static void	set_texture_color(unsigned char *rgb, int pos, t_data *data)
{
	rgb[0] = *(data->texture->pixel_addr + pos);
	rgb[1] = *(data->texture->pixel_addr + pos + 1);
	rgb[2] = *(data->texture->pixel_addr + pos + 2);
}

static int	get_texture_color(int pos, t_data *data)
{
	unsigned char	rgb[3];

	if (data->texture->bpp == 32)
		return (*(unsigned int *)(data->texture->pixel_addr + pos));
	set_texture_color(rgb, pos, data);
	return (create_trgb(255, rgb[2], rgb[1], rgb[0]));
}

static int	calculate_pos(double y_offset, double x_offset, t_data *data)
{
	return (((int)y_offset * data->texture->line_lenght) + ((int)x_offset
			* (data->texture->bpp / 8)));
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix,
		double wall_h)
{
	t_texture	*texture;
	double		x_offset;
	double		y_offset;
	double		step;
	int			color;

	texture = get_texture(data, data->ray->inter_h);
	if (!texture || !texture->img)
		return ;
	step = (double)texture->s_y / wall_h;
	x_offset = get_texture_x_offset(texture, data);
	y_offset = (top_pix - (SCREEN_H / 2) + (wall_h / 2)) * step;
	if (y_offset < 0)
		y_offset = 0;
	while (top_pix < bot_pix && (int)y_offset < texture->s_y)
	{
		color = get_texture_color(calculate_pos(y_offset,
												x_offset,
												data),
									data);
		my_mlx_pixel_put(data, ray, top_pix, color);
		y_offset += step;
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
	draw_wall(data, ray, top_pix, bot_pix, wall_h);
	draw_plafond_sol(data, ray, top_pix, bot_pix);
}
