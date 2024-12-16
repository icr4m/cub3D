/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:04:28 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/16 16:05:07 by erwfonta         ###   ########.fr       */
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

int		is_near_door(t_data *data);
void	update_door(t_data *data);
t_door  *find_door(t_data *data, float x, float y);

#endif