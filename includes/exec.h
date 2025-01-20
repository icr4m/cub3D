/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:03:59 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 15:22:16 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "cub3d.h"

void		cast_rayons(t_data *data);

float		cal_horizontal_inter(t_data *data, float angle);
float		cal_vertical_inter(t_data *data, float angle);
void		minimap_manager(t_data *data);
void		handle_basic_controls(int keynb, t_data *data);
int			inter_check(float angle, float *inter, float *step, int is_horizon);
float		nor_angle(float angle);
int			unit_circle(float angle, char c);
int			no_wall_hit(t_data *data, float co_x, float co_y);
void		draw_plafond_sol(t_data *data, int ray, int top_pix, int bot_pix);
void		start_game(t_data *data);
int			loop_render_game(t_data *data);
double		get_texture_x_offset(t_texture *texture, t_data *data);

float		calculate_distance_to_door(t_data *data, int door_x, int door_y);
int			is_near_door(t_data *data, int door_x, int door_y);
void		update_door(t_data *data, t_doors *door, int x, int y);

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

void		move_player(t_data *data, double move_x, double move_y);

void		manager_player(t_data *data);
void		rotate_mouse(t_data *data, int flag);

void		cast_curseur(t_data *data);
void		draw_minimap(t_data *data);

int			is_within_bounds(t_data *data, float co_x, float co_y);
int			calculate_door_index(t_data *data, int x, int y);
int			handle_vertical_door(t_data *data, int y, float co_y,
				int door_index);
int			handle_horizontal_door(t_data *data, int x, float co_x,
				int door_index);
int			is_vertical_door(t_data *data, int x, int y);

#endif