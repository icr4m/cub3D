/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:28:43 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 15:40:39 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_interaction_text(t_data *data)
{
	int	door_index;
	int	y;
	int	x;

	door_index = 0;
	y = 0;
	while (y < (int)(data->amount_l - data->l_map_start))
	{
		x = 0;
		while (x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42 && data->doors[door_index]->is_near)
			{
				mlx_string_put(data->mlx_ptr, data->win_ptr, SCREEN_W / 2.2,
					SCREEN_H / 1.5, 0xEC8921, "Press E to interact");
				return ;
			}
			if (data->map_2d[y][x] == 42)
				door_index++;
			x++;
		}
		y++;
	}
}

int	loop_render_game(t_data *data)
{
	int	x;
	int	y;
	int	door_index;

	door_index = 0;
	y = 0;
	while (y < (int)(data->amount_l - data->l_map_start))
	{
		x = 0;
		while (x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
				update_door(data, data->doors[door_index++], x, y);
			x++;
		}
		y++;
	}
	manager_player(data);
	cast_rayons(data);
	if (data->is_minimap == 1)
		draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0,
		0);
	draw_interaction_text(data);
	return (0);
}
