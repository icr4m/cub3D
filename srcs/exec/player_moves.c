/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:40:57 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 14:04:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_KEY;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_KEY;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	rotate_mouse(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_MOUSE;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_MOUSE;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	set_movement_values(t_data *data, double *move_x, double *move_y)
{
	if (data->player->lr_flag == 1)
	{
		*move_x = -sin(data->player->angle);
		*move_y = cos(data->player->angle);
	}
	else if (data->player->lr_flag == -1)
	{
		*move_x = sin(data->player->angle);
		*move_y = -cos(data->player->angle);
	}
	else if (data->player->ud_flag == 1)
	{
		*move_x = cos(data->player->angle);
		*move_y = sin(data->player->angle);
	}
	else if (data->player->ud_flag == -1)
	{
		*move_x = -cos(data->player->angle);
		*move_y = -sin(data->player->angle);
	}
	*move_x *= (data->player->speed + data->player->is_sprinting);
	*move_y *= (data->player->speed + data->player->is_sprinting);
}

void	manager_player(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	if (data->player->rot_flag == 1)
		rotate_player(data, 1);
	if (data->player->rot_flag == -1)
		rotate_player(data, 0);
	set_movement_values(data, &move_x, &move_y);
	move_player(data, move_x, move_y);
}
