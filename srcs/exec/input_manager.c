/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 02:37:38 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_doors(t_data *data)
{
	int	door_index;
	int	x;
	int	y;

	door_index = 0;
	y = -1;
	while (++y < (int)(data->amount_l - data->l_map_start))
	{
		x = -1;
		while (++x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
			{
				if (data->doors[door_index]->is_near)
				{
					data->doors[door_index]->is_moving = 1;
					data->doors[door_index]->opening = (data->doors[door_index]->position < 0.5);
				}
				door_index++;
			}
		}
	}
}

int	press_manager(int keynb, t_data *data)
{
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == M)
		minimap_manager(data);
	handle_basic_controls(keynb, data);
	if (keynb == E)
		handle_doors(data);
	return (0);
}

int	release_manager(int keynb, t_data *data)
{
	if (keynb == LEFT2)
		data->player->lr_flag = 0;
	if (keynb == RIGHT2)
		data->player->lr_flag = 0;
	if (keynb == DOWN2)
		data->player->ud_flag = 0;
	if (keynb == UP2)
		data->player->ud_flag = 0;
	if (keynb == LEFT)
		data->player->rot_flag = 0;
	if (keynb == RIGHT)
		data->player->rot_flag = 0;
	if (keynb == SHIFT)
		data->player->is_sprinting = 0;
	if (keynb == 65535)
		data->player->is_sprinting = 0;
	return (0);
}

int	close_windows(t_data *data)
{
	exit_and_free(EXIT_SUCCESS, data);
	return (0);
}

int	mouse_manager(int x, int y, t_data *data)
{
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	if (x == SCREEN_W / 2 && y == SCREEN_H / 2)
		return (0);
	if (x >= SCREEN_W / 2)
		rotate_mouse(data, 1);
	else
		rotate_mouse(data, 0);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 2);
	return (0);
}
