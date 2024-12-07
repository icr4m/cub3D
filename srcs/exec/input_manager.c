/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:14:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_manager(int keynb, t_data *data)
{
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == LEFT2)
		data->player->lr_flag = -1;
	if (keynb == RIGHT2)
		data->player->lr_flag = 1;
	if (keynb == DOWN2)
		data->player->ud_flag = -1;
	if (keynb == UP2)
		data->player->ud_flag = 1;
	if (keynb == LEFT)
		data->player->rot_flag = -1;
	if (keynb == RIGHT)
		data->player->rot_flag = 1;
	if (keynb == SHIFT)
		data->player->is_sprinting = SPRINT_VALUE;
	if (keynb == 65535)
		data->player->is_sprinting = 13;
	return (0);
}

int	release_manager(int keynb, t_data *data)
{
	if (keynb == LEFT2)
		data->player->lr_flag = 0;
	if (keynb == RIGHT2)
		data->player->lr_flag = 0;
	if (keynb == DOWN2)
		data->player->ud_flag = 0;
	if (keynb == UP2)
		data->player->ud_flag = 0;
	if (keynb == LEFT)
		data->player->rot_flag = 0;
	if (keynb == RIGHT)
		data->player->rot_flag = 0;
	if (keynb == SHIFT)
		data->player->is_sprinting = 0;
	if (keynb == 65535)
		data->player->is_sprinting = 0;
	return (0);
}

int	close_windows(t_data *data)
{
	exit_and_free(EXIT_SUCCESS, data);
	return (0);
}

int	mouse_manager(int x, int y, t_data *data)
{
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	if (x == SCREEN_W / 2 && y == SCREEN_H / 2)
		return (0);
	if (x >= SCREEN_W / 2)
		rotate_mouse(data, 1);
	else
		rotate_mouse(data, 0);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 2);
	return (0);
}
