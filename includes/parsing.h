/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:27:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 20:38:06 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void	check_walls(t_data *data);
void	check_player(t_data *data);
void	check_color(t_data *data);

void	parse_map(t_data *data, char **av);
void	start_parse(t_data *data, char **av);
int		test_identifier(char *line, t_data *data);

void	check_file_cub(char *name);
size_t	calculate_max_c(t_data *data, char *line);

void	start_mlx(t_data *data);

#endif