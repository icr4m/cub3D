#ifndef EXEC_H
# define EXEC_H

# include "cub3d.h"

void		cast_rayons(t_data *data);

int			inter_check(float angle, float *inter, float *step, int is_horizon);
float		nor_angle(float angle);
int			unit_circle(float angle, char c);
int			no_wall_hit(t_data *data, float co_x, float co_y);

void		start_game(t_data *data);
int			loop_render_game(t_data *data);

void		render_wall(t_data *data, int ray);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
t_texture	*get_texture(t_data *data, int i);
int			get_pixel_color(t_texture *texture, int x, int y);

int			press_manager(int keynb, t_data *data);
int			release_manager(int keynb, t_data *data);
int			close_windows(t_data *data);
int			input_manager(int keynb, t_data *data);
int			mouse_manager(int x, int y, t_data *data);

void		manager_player(t_data *data);
void		rotate_mouse(t_data *data, int flag);

void		cast_curseur(t_data *data);
void		draw_minimap_walls(t_data *data, float player_x, float player_y);

#endif