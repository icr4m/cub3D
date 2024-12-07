/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:32:03 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 14:57:51 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_SIZE 150  // Base size of minimap
#define MINIMAP_SCALE 0.2 // Scale factor for elements within minimap

void	draw_player_direction(t_data *data, int center_x, int center_y)
{
	int		line_length;
	int		end_x;
	int		end_y;
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	// Draw player direction line
	line_length = 15;
	end_x = center_x + cos(data->player->angle) * line_length;
	end_y = center_y + sin(data->player->angle) * line_length;
	// Draw a yellow line showing player direction
	dx = end_x - center_x;
	dy = end_y - center_y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = center_x;
	y = center_y;
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFFFF00);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_minimap_walls(t_data *data, float player_x, float player_y)
{
	int		start_y;
	float	scale;
	int		player_tile_x;
	int		player_tile_y;
	int		visible_range;
	int		map_x;
	int		map_y;
	int		draw_x;
	int		draw_y;
	int		color;
	int		player_draw_x;
	int		player_draw_y;
	int		minimap_size;
	int		start_x;

	minimap_size = MINIMAP_SIZE * (SCREEN_W / 1920.0);
	// Scale with screen width
	start_x = 20;
	// Padding from screen edge
	start_y = 20;
	scale = MINIMAP_SCALE * (SCREEN_W / 1920.0);
	// Calculate player's position in tile coordinates
	player_tile_x = player_x / TILE_SIZE;
	player_tile_y = player_y / TILE_SIZE;
	// Calculate visible range (number of tiles visible in each direction)
	visible_range = minimap_size / (TILE_SIZE * scale) / 2;
	// Draw the visible portion of the map
	for (int y = -visible_range; y <= visible_range; y++)
	{
		for (int x = -visible_range; x <= visible_range; x++)
		{
			map_x = player_tile_x + x;
			map_y = player_tile_y + y;
			// Check if the current position is within map bounds
			if (map_x >= 0 && map_x < (int)data->amount_c && map_y >= 0
				&& map_y < (int)(data->amount_l - data->l_map_start))
			{
				// Calculate position on minimap
				draw_x = start_x + (x + visible_range) * (TILE_SIZE * scale);
				draw_y = start_y + (y + visible_range) * (TILE_SIZE * scale);
				// Draw walls and floor
				for (int py = 0; py < TILE_SIZE * scale; py++)
				{
					for (int px = 0; px < TILE_SIZE * scale; px++)
					{
						if (data->map_2d[map_y][map_x] == 1)
						{
							color = 0x808080; // Gray for walls
						}
						else if (data->map_2d[map_y][map_x] == 42)
						{
							color = 0x8B4513; // Brown for doors
						}
						else
						{
							color = 0x1A1A1A; // Dark gray for floor
						}
						my_mlx_pixel_put(data, draw_x + px, draw_y + py, color);
					}
				}
			}
		}
	}
	// Draw player
	player_draw_x = start_x + minimap_size / 2;
	player_draw_y = start_y + minimap_size / 2;
	for (int py = -2; py <= 2; py++)
	{
		for (int px = -2; px <= 2; px++)
		{
			my_mlx_pixel_put(data, player_draw_x + px, player_draw_y + py,
				0xFF0000);
		}
	}
	// Draw player direction
	draw_player_direction(data, player_draw_x, player_draw_y);
	// Draw minimap border
	for (int i = 0; i < minimap_size; i++)
	{
		my_mlx_pixel_put(data, start_x + i, start_y, 0xFFFFFF);
		// Top
		my_mlx_pixel_put(data, start_x + i, start_y + minimap_size, 0xFFFFFF);
		// Bottom
		my_mlx_pixel_put(data, start_x, start_y + i, 0xFFFFFF);
		// Left
		my_mlx_pixel_put(data, start_x + minimap_size, start_y + i, 0xFFFFFF);
		// Right
	}
}
