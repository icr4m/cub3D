/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:12 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 15:14:59 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef enum e_key
{
	UP = 65362,
	UP2 = 119,
	RIGHT = 65363,
	RIGHT2 = 100,
	LEFT = 65361,
	LEFT2 = 97,
	DOWN = 65364,
	DOWN2 = 115,
	ECHAP = 65307,
	CLOSE_ICON = 17,
	SHIFT = 65505,
	E = 101,
	M = 109
}						t_key;

typedef struct s_point
{
	int					co_x;
	int					co_y;
}						t_point;

typedef struct s_move_data
{
	int					new_x;
	int					new_y;
	int					map_x;
	int					map_y;
}						t_move_data;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct s_img
{
	void				*img_ptr;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_player
{
	t_point				co;
	double				angle;
	float				fov;
	int					rot_flag;
	int					lr_flag;
	int					ud_flag;
	float				speed;
	double				is_sprinting;
}						t_player;

typedef struct s_doors
{
	float				position;
	int					is_moving;
	int					is_near;
	int					opening;
	float				speed;

}						t_doors;

typedef struct s_rayon
{
	double				distance;
	double				angle;
	bool				inter_h;
	bool				is_door;
	float				wall_hit_x;
	float				wall_hit_y;
}						t_rayon;

typedef struct s_texture
{
	int					s_x;
	int					s_y;
	void				*img;
	char				*identifier;
	char				*path;
	struct s_texture	*next;
	int					bpp;
	char				*pixel_addr;
	int					line_lenght;
	int					endian;
}						t_texture;

typedef struct s_data
{
	t_doors				**doors;
	int					nb_doors;
	double				wall_h;
	bool				is_minimap;
	void				*mlx_ptr;
	void				*win_ptr;
	size_t				l_map_start;
	size_t				amount_l_map;
	size_t				amount_l;
	size_t				amount_c;
	t_player			*player;
	t_rayon				*ray;
	t_point				start_player_pos;
	int					p_id;
	int					**map_2d;
	int					fd;
	t_texture			*texture;
	t_rgb				*floor;
	t_rgb				*ceiling;
	t_img				*img;
}						t_data;

#endif