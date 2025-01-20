/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_wall_hit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:24:40 by rsk               #+#    #+#             */
/*   Updated: 2025/01/20 02:40:24 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_within_bounds(t_data *data, float co_x, float co_y)
{
	int	x;
	int	y;

	if (co_x < 0 || co_y < 0)
		return (0);
	x = floor(co_x / TILE_SIZE);
	y = floor(co_y / TILE_SIZE);
	return (x < (int)data->amount_c && y < (int)(data->amount_l
			- data->l_map_start));
}

int	calculate_door_index(t_data *data, int x, int y)
{
	int	door_index;
	int	i;
	int	j;

	door_index = 0;
	i = 0;
	while (i < y)
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
	j = 0;
	while (j < x)
	{
		if (data->map_2d[y][j] == 42)
			door_index++;
		j++;
	}
	return (door_index);
}

int	handle_vertical_door(t_data *data, int y, float co_y, int door_index)
{
	float	door_y;

	door_y = y * TILE_SIZE + data->doors[door_index]->position * TILE_SIZE;
	if (co_y < door_y)
	{
		data->ray->is_door = 1;
		return (0);
	}
	data->ray->is_door = 0;
	return (1);
}

int	handle_horizontal_door(t_data *data, int x, float co_x, int door_index)
{
	float	door_x;

	door_x = x * TILE_SIZE + data->doors[door_index]->position * TILE_SIZE;
	if (co_x < door_x)
	{
		data->ray->is_door = 1;
		return (0);
	}
	data->ray->is_door = 0;
	return (1);
}

int	is_vertical_door(t_data *data, int x, int y)
{
	return (y > 0 && data->map_2d[y - 1][x] == 1 &&
			y < (int)(data->amount_l - data->l_map_start) &&
			data->map_2d[y + 1][x] == 1);
}
