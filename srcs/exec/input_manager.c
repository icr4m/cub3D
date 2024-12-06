/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/06 15:29:37 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_manager(int keynb, t_data *data)
{
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
	return (0);
}

int	close_windows(t_data *data)
{
	exit_and_free(EXIT_SUCCESS, data);
	return (0);
}

int	mouse_manager(int x, int y, t_data *data)
{
	static int	old_x;

	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	if (!old_x)
		old_x = x;
	else
	{
		if (x < old_x)
			rotate_mouse(data, 0);
		else
			rotate_mouse(data, 1);
		old_x = x;
	}
	printf("x: %d y: %d \n", x, y);
	return (0);
}
