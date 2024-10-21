/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:05:15 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 18:24:29 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_cub(char *name)
{
	const size_t	len = ft_strlen(name);

	if (name[len - 3] != 'c' || name[len - 2] != 'u' || name[len - 1] != 'b')
		free_and_exit(EXIT_FAILURE, "The map should be .cub map");
	if (open(name, O_RDONLY) == -1)
		free_and_exit(EXIT_FAILURE, "Permission denied on the map");
}

int	test_identifier(char *line)
{
	if (ft_strncmp(line, ID_NO, 3) == 0)
		return (1);
	else if (ft_strncmp(line, ID_SO, 3) == 0)
		return (1);
	else if (ft_strncmp(line, ID_EA, 3) == 0)
		return (1);
	else if (ft_strncmp(line, ID_WE, 3) == 0)
		return (1);
	else if (ft_strncmp(line, ID_F, 2) == 0)
		return (1);
	else if (ft_strncmp(line, ID_C, 2) == 0)
		return (1);
	return (0);
}