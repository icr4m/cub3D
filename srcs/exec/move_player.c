/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:02:23 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 17:23:59 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_door_row_index(t_data *data, int map_y)
{
	int	i;
	int	j;
	int	door_index;

	i = 0;
	door_index = 0;
	while (i < map_y)
	{
		j = 0;
		while (j < (int)data->amount_c)
		{
			if (data->map_2d[i][j] == 42)
				door_index++;
			j++;
		}
		i++;
	}
	return (door_index);
}

static int	get_door_col_index(t_data *data, int map_y, int map_x)
{
	int	j;
	int	door_index;

	j = 0;
	door_index = 0;
	while (j < map_x)
	{
		if (data->map_2d[map_y][j] == 42)
			door_index++;
		j++;
	}
	return (door_index);
}

static int	is_door_blocked(t_data *data, t_move_data *move)
{
	int	door_index;

	if (data->map_2d[move->map_y][move->map_x] != 42)
		return (0);
	door_index = get_door_row_index(data, move->map_y);
	door_index += get_door_col_index(data, move->map_y, move->map_x);
	if (data->doors[door_index]->position > 0.1)
		return (1);
	return (0);
}

static void	adjust_position(t_data *data, t_move_data *move)
{
	if (move->new_x % TILE_SIZE == 0 && data->map_2d[move->map_y][move->map_x
		- 1] == 1)
		move->new_x += 1;
	if (move->new_y % TILE_SIZE == 0 && data->map_2d[move->map_y
			- 1][move->map_x] == 1)
		move->new_y += 1;
}

void	move_player(t_data *data, double move_x, double move_y)
{
	t_move_data	move;

	move.new_x = roundf(data->player->co.co_x + move_x);
	move.new_y = roundf(data->player->co.co_y + move_y);
	move.map_x = (move.new_x / TILE_SIZE);
	move.map_y = (move.new_y / TILE_SIZE);
	if (is_door_blocked(data, &move))
		return ;
	adjust_position(data, &move);
	if (data->map_2d[move.map_y][move.map_x] != 1
		&& data->map_2d[move.map_y][data->player->co.co_x / TILE_SIZE] != 1
		&& data->map_2d[data->player->co.co_y / TILE_SIZE][move.map_x] != 1)
	{
		data->player->co.co_x = move.new_x;
		data->player->co.co_y = move.new_y;
	}
}
