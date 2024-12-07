/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_curseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:05:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/06 17:22:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_curseur(t_data *data)
{
	int	size;
	int	start_x;
	int	start_y;
	int	y;
	int	x;

	size = 5;
	start_x = SCREEN_W / 2 - size / 2;
	start_y = SCREEN_H / 2 - size / 2;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (y == 2 && x == 2)
				my_mlx_pixel_put(data, start_x + x, start_y + y, 0xFFFF00);
			else
				my_mlx_pixel_put(data, start_x + x, start_y + y, 0x000000);
			x++;
		}
		y++;
	}
}
