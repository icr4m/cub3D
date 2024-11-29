/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:04:28 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 18:19:31 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "cub3d.h"

void	init_cub(t_data *data);

void	free_and_exit(int code, char *message);
void	handle_malloc_error(char *message, t_data *data);

#endif