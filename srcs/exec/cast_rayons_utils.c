/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:27:15 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 17:19:59 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_intersection: Vérifie et ajuste les calculs d'intersection pour le
** ray-casting
** @param angle: angle du rayon en radians
** @param inter: pointeur vers la position de l'intersection (modifié
** selon la direction)
** @param step: pointeur vers la valeur du pas (inversé si nécessaire)
** @param is_horizon: booléen - 1 pour intersection horizontale,
	0 pour verticale
** @return: -1 si TILE_SIZE est ajouté à l'intersection, 1 sinon
*/
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

/*
** Normalise un angle en radians pour le maintenir entre 0 et 2π
** @param angle: angle en radians à normaliser
** @return: angle normalisé entre 0 et 2π
*/
float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	no_wall_hit(t_data *data, float co_x, float co_y)
{
	int	x;
	int	y;
	int	door_index;

	if (!is_within_bounds(data, co_x, co_y))
		return (0);
	x = floor(co_x / TILE_SIZE);
	y = floor(co_y / TILE_SIZE);
	if (!data->map_2d[y] || x > (int)data->amount_c)
	{
		data->ray->is_door = 0;
		return (1);
	}
	if (data->map_2d[y][x] == 1)
		return (0);
	if (data->map_2d[y][x] == 42)
	{
		door_index = calculate_door_index(data, x, y);
		if (is_vertical_door(data, x, y))
			return (handle_vertical_door(data, y, co_y, door_index));
		else
			return (handle_horizontal_door(data, x, co_x, door_index));
	}
	data->ray->is_door = 0;
	return (1);
}
