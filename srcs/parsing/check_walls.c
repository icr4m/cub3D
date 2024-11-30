/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:32:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 03:34:30 by ijaber           ###   ########.fr       */
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
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[nb_line - 1][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
	i = 0;
	while (i < nb_line)
	{
		if (data->map_2d[i][0] != 1 || data->map_2d[i][data->amount_c - 1] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR);
		i++;
	}
}
