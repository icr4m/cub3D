/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:05:15 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/28 22:58:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_cub(char *name)
{
	const size_t	len = ft_strlen(name);

	if (name[len - 3] != 'c' || name[len - 2] != 'u' || name[len - 1] != 'b')
		free_and_exit(EXIT_FAILURE, "The map should be .cub map");
}
