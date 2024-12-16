/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:30:19 by erwfonta          #+#    #+#             */
/*   Updated: 2024/12/16 15:45:50 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_near_door(t_data *data)
{
	float	player_x;
	float	player_y;
	float	door_center_x;
	float	door_center_y;
	float	distance;

	player_x = data->player->co.co_x;
	player_y = data->player->co.co_y;
	for (int i = 0; i < data->nb_doors; i++)
	{
		door_center_x = (data->doors[i]->x * TILE_SIZE) + (TILE_SIZE / 2);
		door_center_y = (data->doors[i]->y * TILE_SIZE) + (TILE_SIZE / 2);
		distance = sqrt(pow(player_x - door_center_x, 2) + pow(player_y
					- door_center_y, 2));
		if (distance < TILE_SIZE * 1.5)
			return (1);
	}
	return (0);
}

void	update_door(t_data *data)
{
	for (int i = 0; i < data->nb_doors; i++)
	{
		t_door *door = data->doors[i];

		if (door->state == 1)
		{
			door->factor -= 0.03;
			if (door->factor <= 0)
			{
				door->factor = 0;
				door->state = 2;
			}
		}
		else if (door->state == 3)
		{
			door->factor += 0.03;
			if (door->factor >= 1)
			{
				door->factor = 1;
				door->state = 0;
			}
		}
	}
}