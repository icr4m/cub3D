/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:05:15 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 05:27:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_cub(char *name)
{
	const size_t	len = ft_strlen(name);

	if (name[len - 3] != 'c' || name[len - 2] != 'u' || name[len - 1] != 'b')
		free_and_exit(EXIT_FAILURE, "The map should be .cub map");
}

size_t	calculate_max_c(t_data *data, char *line)
{
	size_t max_strlen = 0;

	while (line)
	{
		if (max_strlen < ft_strlen(line))
			max_strlen = ft_strlen(line);
		gc_free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	return (max_strlen);
}