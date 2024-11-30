/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:25:54 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 00:09:21 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_map_parsing(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	width;

	printf("\n=== TEST MAP PARSING ===\n");
	// Affichage de la map avec symboles pour plus de clarté
	i = 0;
	while (i <= data->amount_l - data->l_map_start)
	{
		j = 0;
		width = 33;
		while (j < width)
		{
			if (data->map_2d[i][j] == 0)
				printf("  "); // FLOOR
			else if (data->map_2d[i][j] == 1)
				printf("🧱"); // WALL
			else if (data->map_2d[i][j] == 11)
				printf("↑ "); // PLAYER_N
			else if (data->map_2d[i][j] == 12)
				printf("↓ "); // PLAYER_S
			else if (data->map_2d[i][j] == 13)
				printf("→ "); // PLAYER_E
			else if (data->map_2d[i][j] == 14)
				printf("← "); // PLAYER_W
			else if (data->map_2d[i][j] == 42)
				printf("🚪"); // DOOR
			else
				printf("❌"); // UNKNOWN
			j++;
		}
		printf("\n");
		i++;
	}
	// Affichage numérique pour debug
	printf("\n=== NUMERIC VALUES ===\n");
	i = 0;
	while (i <= data->amount_l - data->l_map_start)
	{
		j = 0;
		width = 34;
		while (j < width)
		{
			printf("%2d ", data->map_2d[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\nMap height: %zu\n", data->amount_l - data->l_map_start);
}
