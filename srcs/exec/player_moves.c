/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:40:57 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/12 12:52:22 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double move_x, double move_y)
{
	int		map_x;
	int		map_y;
	int		new_x;
	int		new_y;
	double	dnew_x;
	double	dnew_y;

	dnew_x = data->player->co.co_x + move_x;
	dnew_y = data->player->co.co_y + move_y;
	printf("test x:%.6f\n", dnew_x);
	printf("test y:%.6f\n", dnew_y);
	new_x = roundf(dnew_x);
	new_y = roundf(dnew_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	printf("new x:%d\n", map_x);
	printf("new y:%d\n", map_y);
	if (new_x % TILE_SIZE == 0)
		new_x += 1;
	if (new_y % TILE_SIZE == 0)
		new_y += 1;
	// if (map_x >= (int)data->amount_c || map_y >= (int)data->amount_l
	// 	- (int)data->l_map_start || map_x <= 0 || map_y <= 0)
	// 	return ;
	if (data->map_2d[map_y][map_x] != 1
		&& data->map_2d[map_y][data->player->co.co_x / TILE_SIZE] != 1
		&& data->map_2d[data->player->co.co_y / TILE_SIZE][map_x] != 1)
	{
		data->player->co.co_x = new_x;
		data->player->co.co_y = new_y;
	}
}

void	rotate_player(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_KEY;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_KEY;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	rotate_mouse(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_MOUSE;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_MOUSE;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	manager_player(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	if (data->player->rot_flag == 1)
		rotate_player(data, 1);
	if (data->player->rot_flag == -1)
		rotate_player(data, 0);
	if (data->player->lr_flag == 1)
	{
		move_x = -sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->lr_flag == -1)
	{
		move_x = sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = -cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->ud_flag == 1)
	{
		move_x = cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->ud_flag == -1)
	{
		move_x = -cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = -sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	move_player(data, move_x, move_y);
}
