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
}						t_key;

typedef struct s_point
{
	int					co_x;
	int					co_y;
}						t_point;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

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

typedef struct s_rayon
{
	double				distance;
	double				angle;
	int					inter_h;
	int					is_door;
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
}						t_texture;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	size_t				l_map_start;
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
}						t_data;

#endif