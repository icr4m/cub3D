/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:28:43 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/16 16:11:40 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_render_game(t_data *data)
{
	data->near_door = is_near_door(data);
	update_door(data);
	manager_player(data);
	cast_rayons(data);
	if (data->is_minimap == 1)
		draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0,
		0);
	if (data->near_door)
		mlx_string_put(data->mlx_ptr, data->win_ptr, SCREEN_W / 2 - 100,
			SCREEN_H - 300, 0xFFFFFF, "Press E to interact");
	return (0);
}
