/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/16 15:42:34 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_manager(t_data *data)
{
	if (data->is_minimap == 0)
		data->is_minimap = 1;
	else if (data->is_minimap == 1)
		data->is_minimap = 0;
}

int	press_manager(int keynb, t_data *data)
{
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == M)
		minimap_manager(data);
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
	if(keynb == E && data->near_door)
	{
		float player_x = data->player->co.co_x;
        float player_y = data->player->co.co_y;
        
        for (int i = 0; i < data->nb_doors; i++)
        {
            float door_x = data->doors[i]->x * TILE_SIZE + TILE_SIZE / 2;
            float door_y = data->doors[i]->y * TILE_SIZE + TILE_SIZE / 2;
            float distance = sqrt(pow(player_x - door_x, 2) + pow(player_y - door_y, 2));
            
            if (distance < TILE_SIZE * 1.5)
            {
                if (data->doors[i]->state == 0)  // Si fermée
                    data->doors[i]->state = 1;   // Commencer à ouvrir
                else if (data->doors[i]->state == 2)  // Si ouverte
                    data->doors[i]->state = 3;   // Commencer à fermer
                break;
            }
        }
	}
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
