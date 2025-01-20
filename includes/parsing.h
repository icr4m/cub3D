/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:27:32 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 02:49:04 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void		check_walls(t_data *data);
void		check_player(t_data *data);
void		check_color(t_data *data);

void		parse_map(t_data *data, char **av);
void		start_parse(t_data *data, char **av);
int			test_identifier(char *line, t_data *data);

void		check_file_cub(t_data *data, char *name);
size_t		calculate_max_c(t_data *data, char *line);

void		init_doors(t_data *data);

void		start_mlx(t_data *data);

t_texture	*search_texture(t_data *data, char *identifier);

#endif