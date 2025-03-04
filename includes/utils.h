/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:04:28 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/03 15:17:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "cub3d.h"

void	init_cub(t_data *data, char **av);

void	free_and_exit(int code, char *message, t_data *data);
void	handle_malloc_error(char *message, t_data *data);
void	exit_and_free(int code, t_data *data);

void	test_map_parsing(t_data *data);
void	affiche_texture_debug(t_data data);

#endif