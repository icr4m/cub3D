/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:32:42 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/16 16:06:50 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(t_data *data)
{
	size_t	x;
	size_t	y;
	int		door_count;

	y = 0;
	door_count = 0;
	while (y < data->amount_l - data->l_map_start)
	{
		x = 0;
		while (x < data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
				door_count++;
			x++;
		}
		y++;
	}
	data->doors = gc_malloc(sizeof(t_door *) * door_count);
	if (!data->doors)
		handle_malloc_error("doors allocation", data);
	data->nb_doors = door_count;
	door_count = 0;
	y = 0;
	while (y < data->amount_l - data->l_map_start)
	{
		x = 0;
		while (x < data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
			{
				data->doors[door_count] = gc_malloc(sizeof(t_door));
				if (!data->doors[door_count])
					handle_malloc_error("door allocation", data);
				data->doors[door_count]->state = 0;
				data->doors[door_count]->factor = 1.0;
				data->doors[door_count]->x = x;
				data->doors[door_count]->y = y;
				data->doors[door_count]->ignore_interact = 0;
				door_count++;
			}
			x++;
		}
		y++;
	}
}

static void	init_player(t_data *data)
{
	data->player->co.co_x = data->start_player_pos.co_x * TILE_SIZE + TILE_SIZE
		/ 2;
	data->player->co.co_y = data->start_player_pos.co_y * TILE_SIZE + TILE_SIZE
		/ 2;
	if (data->p_id == 11)
		data->player->angle = (M_PI * 3 / 2);
	if (data->p_id == 12)
		data->player->angle = M_PI / 2;
	if (data->p_id == 13)
		data->player->angle = 0;
	if (data->p_id == 14)
		data->player->angle = M_PI;
	data->player->fov = (FOV * M_PI) / 180;
	data->player->speed = START_PLAYER_SPEED;
}

void	start_game(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->ray = ft_calloc(1, sizeof(t_rayon));
	init_player(data);
	init_door(data);
	mlx_loop_hook(data->mlx_ptr, loop_render_game, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, mouse_manager,
		data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &close_windows,
		data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &press_manager, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &release_manager, data);
	mlx_loop(data->mlx_ptr);
}
