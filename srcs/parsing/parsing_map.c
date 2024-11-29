/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:22 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 21:59:45 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	unknown_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == WALL || str[i] == FLOOR || str[i] == PLAYER_E
			|| str[i] == PLAYER_N || str[i] == PLAYER_S || str[i] == PLAYER_W
			|| str[i] == DOOR || str[i] == EMPTY || str[i] == ENDOF)
			i++;
		else
			free_and_exit(EXIT_FAILURE, "Unknown character in the map");
	}
}

void	parse_map(t_data *data, char *line)
{
	size_t	count;

	count = 0;
	(void)data;
	while (line)
	{
		count++;
		unknown_char(line);
		line = get_next_line(data->fd);
	}
}
