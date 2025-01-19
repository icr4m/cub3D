/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:40:57 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/19 17:50:18 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_player(t_data *data, double move_x, double move_y)
{
    int new_x;
    int new_y;
    int map_x;
    int map_y;
    int door_index;

    new_x = roundf(data->player->co.co_x + move_x);
    new_y = roundf(data->player->co.co_y + move_y);
    map_x = (new_x / TILE_SIZE);
    map_y = (new_y / TILE_SIZE);

    // Vérification des portes
    if (data->map_2d[map_y][map_x] == 42)
    {
        // Calculer l'index de la porte
        door_index = 0;
        for (int i = 0; i < map_y; i++)
            for (int j = 0; j < (int)data->amount_c; j++)
                if (data->map_2d[i][j] == 42)
                    door_index++;
        for (int j = 0; j < map_x; j++)
            if (data->map_2d[map_y][j] == 42)
                door_index++;

        // Si la porte est fermée (position proche de 0), bloquer le passage
        if (data->doors[door_index]->position > 0.1)
            return;
    }

    if (new_x % TILE_SIZE == 0 && data->map_2d[map_y][map_x - 1] == 1)
        new_x += 1;
    if (new_y % TILE_SIZE == 0 && data->map_2d[map_y - 1][map_x] == 1)
        new_y += 1;

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
