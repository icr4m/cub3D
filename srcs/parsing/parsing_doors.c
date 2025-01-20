/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:48:04 by rsk               #+#    #+#             */
/*   Updated: 2025/01/20 02:48:41 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_doors(t_data *data)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (++y < (int)(data->amount_l - data->l_map_start))
	{
		x = -1;
		while (++x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
				count++;
		}
	}
	return (count);
}

static void	init_single_door(t_data *data, int count)
{
	data->doors[count] = gc_malloc(sizeof(t_doors));
	if (!data->doors[count])
		handle_malloc_error("door allocation", data);
	data->doors[count]->position = 1;
	data->doors[count]->is_moving = 0;
	data->doors[count]->speed = 0.005;
}

static void	allocate_doors(t_data *data)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (++y < (int)(data->amount_l - data->l_map_start))
	{
		x = -1;
		while (++x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
			{
				init_single_door(data, count);
				count++;
			}
		}
	}
}

void	init_doors(t_data *data)
{
	data->nb_doors = count_doors(data);
	data->doors = gc_malloc(sizeof(t_doors *) * data->nb_doors);
	if (!data->doors)
		handle_malloc_error("door allocation", data);
	allocate_doors(data);
}