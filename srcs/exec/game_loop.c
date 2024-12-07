/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:28:43 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 14:56:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_render_game(t_data *data)
{
	manager_player(data);
	cast_rayons(data);
	draw_minimap_walls(data, data->player->co.co_x, data->player->co.co_y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0,
		0);
	return (0);
}
