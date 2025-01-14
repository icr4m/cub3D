/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:32:03 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/13 15:37:15 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_pixel(t_data *data, int x, int y, float *player_pos)
{
	float	rel_x;
	float	rel_y;
	int		map_x;
	int		map_y;

	rel_x = (x - (SCREEN_W - 100)) / 80.0 * 5;
	rel_y = (y - 100) / 80.0 * 5;
	map_x = floor(player_pos[0] / TILE_SIZE + rel_x);
	map_y = floor(player_pos[1] / TILE_SIZE + rel_y);
	if (map_x >= 0 && map_y >= 0 && map_x < (int)data->amount_c
		&& map_y <= (int)(data->amount_l - data->l_map_start))
	{
		if (data->map_2d[map_y][map_x] == 1)
			my_mlx_pixel_put(data, x, y, 0x87CEEBFF);
		else if (data->map_2d[map_y][map_x] == 42)
			my_mlx_pixel_put(data, x, y, 0xFFA500FF);
		else
			my_mlx_pixel_put(data, x, y, 0xFFFFFFFF);
	}
}

static void	draw_direction_line(t_data *data, int center_x, int center_y)
{
	int		end_x;
	int		end_y;
	float	t;

	end_x = center_x + cos(data->player->angle) * 13;
	end_y = center_y + sin(data->player->angle) * 13;
	t = 0;
	while (t <= 1)
	{
		my_mlx_pixel_put(data, center_x + (end_x - center_x) * t, center_y
			+ (end_y - center_y) * t, 0xFF0000FF);
		t += 0.01;
	}
}

static void	draw_player_indicator(t_data *data, int center_x, int center_y)
{
	int	px;
	int	py;

	py = -1;
	while (py <= 1)
	{
		px = -1;
		while (px <= 1)
		{
			my_mlx_pixel_put(data, center_x + px, center_y + py, 0xFF0000FF);
			px++;
		}
		py++;
	}
}

static int	is_in_circle(int x, int y, int center_x, int center_y)
{
	int	distance;

	distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
	return (distance <= 80);
}

void	draw_minimap(t_data *data)
{
	int		y;
	int		x;
	float	player_pos[2];

	player_pos[0] = data->player->co.co_x;
	player_pos[1] = data->player->co.co_y;
	y = 20;
	while (y <= 180)
	{
		x = SCREEN_W - 180;
		while (x <= SCREEN_W - 20)
		{
			if (is_in_circle(x, y, SCREEN_W - 100, 100))
			{
				draw_minimap_pixel(data, x, y, player_pos);
				if (sqrt(pow(x - (SCREEN_W - 100), 2) + pow(y - 100, 2)) >= 79)
					my_mlx_pixel_put(data, x, y, 0x000000FF);
			}
			x++;
		}
		y++;
	}
	draw_player_indicator(data, SCREEN_W - 100, 100);
	draw_direction_line(data, SCREEN_W - 100, 100);
}
