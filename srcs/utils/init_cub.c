/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:18:45 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 01:13:16 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	calculate_l(int fd)
{
	size_t	count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		gc_free(line);
		line = get_next_line(fd);
	}
	return (count);
}

void	init_cub(t_data *data, char **av)
{
	data->texture = NULL;
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, "Error when open map");
	data->amount_l = calculate_l(data->fd);
	close(data->fd);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, "Error when open map");
}