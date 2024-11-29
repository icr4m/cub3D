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
	size_t				l_map_start;
	int					fd;
	t_texture			*texture;
}						t_data;

#endif