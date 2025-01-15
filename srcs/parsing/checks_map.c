/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:32:31 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/15 13:15:12 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_around(t_data *data, size_t i, size_t j)
{
	if (i == 0 || j == 0 || i >= data->amount_l_map || j >= data->amount_c - 1)
		free_and_exit(EXIT_FAILURE, WALL_ERR, data);
	if (data->map_2d[i + 1][j] == -42 || data->map_2d[i][j + 1] == -42
		|| data->map_2d[i - 1][j] == -42 || data->map_2d[i][j - 1] == -42)
		free_and_exit(EXIT_FAILURE, WALL_ERR, data);
}

void	check_walls(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (i <= data->amount_l_map)
	{
		j = 0;
		while (j < data->amount_c)
		{
			if (data->map_2d[i][j] == 0 || data->map_2d[i][j] == 11
				|| data->map_2d[i][j] == 12 || data->map_2d[i][j] == 13
				|| data->map_2d[i][j] == 14)
				check_around(data, i, j);
			j++;
		}
		i++;
	}
}

void	check_player(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (i < data->amount_l - data->l_map_start)
	{
		j = 0;
		while (j < data->amount_c)
		{
			if (data->map_2d[i][j] == 11 || data->map_2d[i][j] == 12
				|| data->map_2d[i][j] == 13 || data->map_2d[i][j] == 14)
			{
				data->start_player_pos.co_x = j;
				data->start_player_pos.co_y = i;
				data->p_id = data->map_2d[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count < 1)
		free_and_exit(EXIT_FAILURE, NO_P_ERR, data);
	if (count > 1)
		free_and_exit(EXIT_FAILURE, TOO_P_ERR, data);
}
