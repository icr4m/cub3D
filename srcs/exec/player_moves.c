/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:40:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/04 09:29:08 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double move_x, double move_y)
{
	int	map_x;
	int	map_y;
	int	new_x;
	int	new_y;

	new_x = roundf(data->player->co.co_x + move_x);
	new_y = roundf(data->player->co.co_y + move_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	if (data->map_2d[map_y][map_x] != '1'
		&& data->map_2d[map_y][data->player->co.co_x / TILE_SIZE] != '1'
		&& data->map_2d[data->player->co.co_y / TILE_SIZE][map_x] != '1')
	{
		data->player->co.co_x = new_x;
		data->player->co.co_y = new_y;
	}
}

void	rotate_player(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_ROTA;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_ROTA;
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
		move_x = -sin(data->player->angle) * PLAYER_SPEED;
		move_y = cos(data->player->angle) * PLAYER_SPEED;
	}
	if (data->player->lr_flag == -1)
	{
		move_x = sin(data->player->angle) * PLAYER_SPEED;
		move_y = -cos(data->player->angle) * PLAYER_SPEED;
	}
	if (data->player->ud_flag == 1)
	{
		move_x = cos(data->player->angle) * PLAYER_SPEED;
		move_y = sin(data->player->angle) * PLAYER_SPEED;
	}
	if (data->player->ud_flag == -1)
	{
		move_x = -cos(data->player->angle) * PLAYER_SPEED;
		move_y = -sin(data->player->angle) * PLAYER_SPEED;
	}
	move_player(data, move_x, move_y);
}
