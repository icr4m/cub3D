/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:32:03 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 16:23:16 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_filled_circle(t_data *data)
{
	int	center_x;
	int	center_y;
	int	radius;
	int	y;
	int	x;
	int	distance;

	center_x = SCREEN_W - 140;
	center_y = 140;
	radius = 100;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
			if (distance <= radius)
			{
				if (distance == radius || distance == radius - 1)
					my_mlx_pixel_put(data, x, y, 0x000000);
				else
					my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
}
