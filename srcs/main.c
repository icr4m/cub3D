/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 18:49:42 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	data.fd = open(av[1], O_RDONLY);
	(void)ac;
	init_cub(&data);
	check_file_cub(av[1]);
	parse_elements(&data);
	// while (data.texture)
	// {
	// 	printf("id: %s\npath: %s\n", data.texture->identifier,
	// 		data.texture->path);
	// 	data.texture = data.texture->next;
	// }
	// printf("line map start: %zu\n", data.l_map_start);
	gc_free(DESTROY_PTR);
	exit(EXIT_SUCCESS);
}
