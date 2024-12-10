/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/10 17:57:40 by rsk              ###   ########.fr       */
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
	// Vérifier d'abord si c'est une porte
	if (data->ray->is_door == 1)
		return (0xAAA32AFF);
	// Ensuite vérifier le type d'intersection
	if (flag == 0) // Intersections verticales
	{
		if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xFF0000FF); // east wall
	}
	else // Intersections horizontales
	{
		if (data->ray->angle > 0 && data->ray->angle < M_PI)
			return (0x0000FFFF); // south wall
		else
			return (0xFFFF00FF); // north wall
	}
}

double	get_texture_x_offset(t_texture *texture, t_data *data)
{
	double	x_offset;

	if (data->ray->inter_h == 1)
		x_offset = (int)fmod((data->ray->wall_hit_x *
								(texture->s_x / TILE_SIZE)),
								texture->s_x);
	else
		x_offset = (int)fmod((data->ray->wall_hit_y *
								(texture->s_x / TILE_SIZE)),
								texture->s_x);
	return (x_offset);
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix,
		double wall_h)
{
	t_texture		*texture;
	double			x_offset;
	double			y_offset;
	double			step;
	int				color;
	char			*pixel_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				pos;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;

	texture = get_texture(data, data->ray->inter_h);
	if (!texture || !texture->img)
		return ;
	pixel_addr = mlx_get_data_addr(texture->img, &bits_per_pixel, &line_length,
			&endian);
	step = (double)texture->s_y / wall_h;
	x_offset = get_texture_x_offset(texture, data);
	y_offset = (top_pix - (SCREEN_H / 2) + (wall_h / 2)) * step;
	if (y_offset < 0)
		y_offset = 0;
	while (top_pix < bot_pix)
	{
		if ((int)y_offset < texture->s_y)
		{
			pos = ((int)y_offset * line_length) + ((int)x_offset
					* (bits_per_pixel / 8));
			if (bits_per_pixel == 32)
				color = *(unsigned int *)(pixel_addr + pos);
			else
			{
				b = *(pixel_addr + pos);
				g = *(pixel_addr + pos + 1);
				r = *(pixel_addr + pos + 2);
				color = create_trgb(255, r, g, b);
			}
			my_mlx_pixel_put(data, ray, top_pix, color);
		}
		y_offset += step;
		top_pix++;
	}
}

void	render_wall(t_data *data, int ray)
{
	double wall_h;
	double top_pix;
	double bot_pix;

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