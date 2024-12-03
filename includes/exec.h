#ifndef EXEC_H
# define EXEC_H

# include "cub3d.h"

void	cast_rayons(t_data *data);

int		inter_check(float angle, float *inter, float *step, int is_horizon);
float	nor_angle(float angle);
int		unit_circle(float angle, char c);
int		no_wall_hit(t_data *data, float co_x, float co_y);

void	start_game(t_data *data);
int		loop_render_game(t_data *data);

void	render_wall(t_data *data, int ray);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif