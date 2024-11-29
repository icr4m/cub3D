/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:27:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 21:00:11 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void	parse_map(t_data *data, char *line);
void	check_file_cub(char *name);
void	start_parse(t_data *data);
int		test_identifier(char *line, t_data *data);

#endif