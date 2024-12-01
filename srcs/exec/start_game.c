/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:32:42 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/01 13:16:36 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_data *data)
{
	data->player->co.co_x = data->start_player_pos.co_x * TILE_SIZE + TILE_SIZE
		/ 2;
	data->player->co.co_y = data->start_player_pos.co_y * TILE_SIZE + TILE_SIZE
		/ 2;
	if (data->p_id == 11)
		data->player->angle = (M_PI * 3 / 2);
	if (data->p_id == 12)
		data->player->angle = M_PI / 2;
	if (data->p_id == 13)
		data->player->angle = 0;
	if (data->p_id == 14)
		data->player->angle = M_PI;
	data->player->fov = (FOV * M_PI) / 180;
}

void	start_game(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->ray = ft_calloc(1, sizeof(t_rayon));
	init_player(data);
	loop_render_game(data);
	// // function qui prends la loop qui render
	// mlx_loop_hook(data->mlx_ptr, loop_render_game, &data);
	// // function qui attends les keys
	// mlx_key_hook();
	// // function qui fait tourner la mlx
	// mlx_loop(data->mlx_ptr);
}
