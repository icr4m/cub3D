/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 23:25:50 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	init_cub(&data, av);
	check_file_cub(av[1]);
	start_parse(&data);
	test_map_parsing(&data);
	gc_free(DESTROY_PTR);
	exit(EXIT_SUCCESS);
}
