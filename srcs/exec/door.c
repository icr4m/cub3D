/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:19:51 by erwfonta          #+#    #+#             */
/*   Updated: 2025/01/19 17:32:39 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	calculate_distance_to_door(t_data *data, int door_x, int door_y)
{
	float	dist_x;
	float	dist_y;

	dist_x = data->player->co.co_x - (door_x * TILE_SIZE + TILE_SIZE / 2);
	dist_y = data->player->co.co_y - (door_y * TILE_SIZE + TILE_SIZE / 2);
	return (sqrt(pow(dist_x, 2) + pow(dist_y, 2)));
}

int	is_near_door(t_data *data, int door_x, int door_y)
{
	float distance = calculate_distance_to_door(data, door_x, door_y);
	return (distance <= TILE_SIZE * 2); // Distance de détection ajustable
}

void update_door(t_data *data, t_doors *door, int x, int y)
{
    door->is_near = is_near_door(data, x, y);

    if (door->is_moving)
    {
        if (door->opening)
        {
            door->position += door->speed;
            if (door->position >= 1.0)
            {
                door->position = 1.0;
                door->is_moving = 0;
            }
        }
        else
        {
            door->position -= door->speed;
            if (door->position <= 0)
            {
                door->position = 0;
                door->is_moving = 0;
            }
        }
    }
}