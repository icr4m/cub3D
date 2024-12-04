/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/04 09:04:31 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_manager(int keynb, t_data *data)
{
	if (keynb == RIGHT2)
		data->player->lr_flag = -1;
	else if (keynb == LEFT2)
		data->player->lr_flag = 1;
	else if (keynb == DOWN2)
		data->player->ud_flag = -1;
	else if (keynb == UP2)
		data->player->ud_flag = 1;
	else if (keynb == LEFT)
		data->player->rot_flag = -1;
	else if (keynb == RIGHT)
		data->player->rot_flag = 1;
	return (0);
}

int	release_manager(int keynb, t_data *data)
{
	if (keynb == RIGHT2)
		data->player->lr_flag = 0;
	else if (keynb == LEFT2)
		data->player->lr_flag = 0;
	else if (keynb == DOWN2)
		data->player->ud_flag = 0;
	else if (keynb == UP2)
		data->player->ud_flag = 0;
	else if (keynb == LEFT)
		data->player->rot_flag = 0;
	else if (keynb == RIGHT)
		data->player->rot_flag = 0;
	return (0);
}

int	close_windows(t_data *data)
{
	exit_and_free(EXIT_SUCCESS, data);
	return (0);
}

int	input_manager(int keynb, t_data *data)
{
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	return (0);
}
