/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:07:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 18:16:37 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_elements(t_data *data)
{
	char	*line;
	size_t	nb_elem;

	nb_elem = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		if (test_identifier(line))
			nb_elem++;
		line = get_next_line(data->fd);
	}
	if (nb_elem < 6)
		free_and_exit(EXIT_FAILURE, "Not enough elements");
	if (nb_elem > 6)
		free_and_exit(EXIT_FAILURE, "Too much elements");
}
