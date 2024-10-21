/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:08:46 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 17:01:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_texture
{
	int					s_x;
	int					s_y;
	void				*img;
	char				*identifier;
	char				*path;
	struct s_texture	*next;
}						t_texture;

typedef struct s_data
{
	int					fd;
	t_texture			*texture;
}						t_data;

#endif