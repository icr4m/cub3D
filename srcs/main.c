/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/06 13:50:34 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	init_cub(&data, av);
	check_file_cub(av[1]);
	start_parse(&data, av);
	// test_map_parsing(&data), affiche_texture_debug(data);
	start_mlx(&data);
	start_game(&data);
	exit_and_free(EXIT_SUCCESS, &data);
}
