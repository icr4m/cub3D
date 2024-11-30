#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_point
{
	size_t				co_x;
	size_t				co_y;
}						t_point;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

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
	size_t				l_map_start;
	size_t				amount_l;
	size_t				amount_c;
	int					**map_2d;
	int					fd;
	t_texture			*texture;
	t_rgb				*floor;
	t_rgb				*ceiling;
}						t_data;

#endif