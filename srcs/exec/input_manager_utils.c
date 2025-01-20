/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:35:56 by rsk               #+#    #+#             */
/*   Updated: 2025/01/20 02:38:24 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	minimap_manager(t_data *data)
{
	if (data->is_minimap == 0)
		data->is_minimap = 1;
	else if (data->is_minimap == 1)
		data->is_minimap = 0;
}

void	handle_basic_controls(int keynb, t_data *data)
{
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
}
