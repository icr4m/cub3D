/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:32:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 19:57:46 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls(t_data *data)
{
	const size_t	nb_line = data->amount_l - data->l_map_start;
	size_t			i;

	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[0][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
		i++;
	}
	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[nb_line][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
		i++;
	}
	i = 0;
	while (i < nb_line)
	{
		if (data->map_2d[i][0] != 1 || data->map_2d[i][data->amount_c - 1] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
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
				count++;
			j++;
		}
		i++;
	}
	if (count < 1)
		free_and_exit(EXIT_FAILURE, NO_P_ERR, data);
	if (count > 1)
		free_and_exit(EXIT_FAILURE, TOO_P_ERR, data);
}
