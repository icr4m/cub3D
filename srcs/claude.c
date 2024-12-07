/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_curseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:05:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/06 17:22:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_curseur(t_data *data)
{
	int	size;
	int	start_x;
	int	start_y;
	int	y;
	int	x;

	size = 5;
	start_x = SCREEN_W / 2 - size / 2;
	start_y = SCREEN_H / 2 - size / 2;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (y == 2 && x == 2)
				my_mlx_pixel_put(data, start_x + x, start_y + y, 0xFFFF00);
			else
				my_mlx_pixel_put(data, start_x + x, start_y + y, 0x000000);
			x++;
		}
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:14:50 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 09:05:58 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	cal_horizontal_inter(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	step_x;
	float	step_y;
	int		orientation;

	step_x = TILE_SIZE / tan(angle);
	step_y = TILE_SIZE;
	h_y = floor(data->player->co.co_y / TILE_SIZE) * TILE_SIZE;
	orientation = inter_check(angle, &h_y, &step_y, 1);
	h_x = data->player->co.co_x + (h_y - data->player->co.co_y) / tan(angle);
	if ((unit_circle(angle, 'y') && step_x > 0) || (!unit_circle(angle, 'y')
			&& step_x < 0))
		step_x *= -1;
	while (no_wall_hit(data, h_x, h_y - orientation))
	{
		h_x += step_x;
		h_y += step_y;
	}
	// if (no_wall_hit(data, h_x, h_y - orientation) == 0)
	// {
	// 	data->ray->wall_hit_x = h_x;
	// 	data->ray->wall_hit_y = h_y;
	// }
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}

float	cal_vertical_inter(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	step_x;
	float	step_y;
	int		orientation;

	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(angle);
	h_x = floor(data->player->co.co_x / TILE_SIZE) * TILE_SIZE;
	orientation = inter_check(angle, &h_x, &step_x, 0);
	h_y = data->player->co.co_y + (h_x - data->player->co.co_x) * tan(angle);
	if ((unit_circle(angle, 'x') && step_y < 0) || (!unit_circle(angle, 'x')
			&& step_y > 0))
		step_y *= -1;
	while (no_wall_hit(data, h_x - orientation, h_y))
	{
		h_x += step_x;
		h_y += step_y;
	}
	// if (no_wall_hit(data, h_x, h_y - orientation) == 0)
	// {
	// 	data->ray->wall_hit_x = h_x;
	// 	data->ray->wall_hit_y = h_y;
	// }
	return (sqrt(pow(h_x - data->player->co.co_x, 2) + pow(h_y
				- data->player->co.co_y, 2)));
}

void	cast_rayons(t_data *data)
{
	double	inter_ve;
	double	inter_ho;
	int		ray;

	ray = 0;
	data->ray->angle = data->player->angle - (data->player->fov / 2);
	while (ray < SCREEN_W)
	{
		data->ray->inter_h = 0;
		data->ray->is_door = 0;
		inter_ho = cal_horizontal_inter(data, nor_angle(data->ray->angle));
		inter_ve = cal_vertical_inter(data, nor_angle(data->ray->angle));
		if (inter_ve <= inter_ho)
			data->ray->distance = inter_ve;
		else
		{
			data->ray->distance = inter_ho;
			data->ray->inter_h = 1;
		}
		ray++;
		data->ray->angle += (data->player->fov / SCREEN_W);
		render_wall(data, ray);
		cast_curseur(data);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rayons_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:27:15 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 08:59:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_intersection: Vérifie et ajuste les calculs d'intersection pour le ray-casting
** @param angle: angle du rayon en radians
** @param inter: pointeur vers la position de l'intersection (modifié selon la direction)
** @param step: pointeur vers la valeur du pas (inversé si nécessaire)
** @param is_horizon: booléen - 1 pour intersection horizontale,
	0 pour verticale
** @return: -1 si TILE_SIZE est ajouté à l'intersection, 1 sinon
*/
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

/*
** Normalise un angle en radians pour le maintenir entre 0 et 2π
** @param angle: angle en radians à normaliser
** @return: angle normalisé entre 0 et 2π
*/
float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	no_wall_hit(t_data *data, float co_x, float co_y)
{
	int	x;
	int	y;

	if (co_x < 0 || co_y < 0)
		return (0);
	x = floor(co_x / TILE_SIZE);
	y = floor(co_y / TILE_SIZE);
	// printf("Checking position: x=%d, y=%d, char=%d\n", x, y,
	// 	data->map_2d[y][x]);
	if ((x >= (int)data->amount_c || y >= (int)(data->amount_l
				- data->l_map_start)))
		return (0);
	if (data->map_2d[y] && x <= (int)data->amount_c)
	{
		if (data->map_2d[y][x] == 1)
			return (0);
		else if (data->map_2d[y][x] == 42)
			return (data->ray->is_door = 1, 0);
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:32:03 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:34:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_filled_circle(t_data *data)
{
	int	distance;

	int center_x = SCREEN_W - 100; // 50 pixels depuis le bord droit
	int center_y = 100;            // 50 pixels depuis le haut
	int radius = 80;               // Rayon du cercle
	int x, y;
	// Dessiner le cercle en utilisant l'algorithme de Bresenham modifié
	for (y = center_y - radius; y <= center_y + radius; y++)
	{
		for (x = center_x - radius; x <= center_x + radius; x++)
		{
			// Calculer la distance du point au centre
			distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
			if (distance <= radius)
			{
				if (distance == radius || distance == radius - 1)
					my_mlx_pixel_put(data, x, y, 0x000000); // Bordure noire
				else
					my_mlx_pixel_put(data, x, y, 0xFFFFFF); // Intérieur blanc
			}
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:28:43 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:33:30 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_render_game(t_data *data)
{
	manager_player(data);
	cast_rayons(data);
	draw_filled_circle(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0,
		0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:51 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:14:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_manager(int keynb, t_data *data)
{
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == ECHAP)
		exit_and_free(EXIT_SUCCESS, data);
	if (keynb == LEFT2)
		data->player->lr_flag = -1;
	if (keynb == RIGHT2)
		data->player->lr_flag = 1;
	if (keynb == DOWN2)
		data->player->ud_flag = -1;
	if (keynb == UP2)
		data->player->ud_flag = 1;
	if (keynb == LEFT)
		data->player->rot_flag = -1;
	if (keynb == RIGHT)
		data->player->rot_flag = 1;
	if (keynb == SHIFT)
		data->player->is_sprinting = SPRINT_VALUE;
	if (keynb == 65535)
		data->player->is_sprinting = 13;
	return (0);
}

int	release_manager(int keynb, t_data *data)
{
	if (keynb == LEFT2)
		data->player->lr_flag = 0;
	if (keynb == RIGHT2)
		data->player->lr_flag = 0;
	if (keynb == DOWN2)
		data->player->ud_flag = 0;
	if (keynb == UP2)
		data->player->ud_flag = 0;
	if (keynb == LEFT)
		data->player->rot_flag = 0;
	if (keynb == RIGHT)
		data->player->rot_flag = 0;
	if (keynb == SHIFT)
		data->player->is_sprinting = 0;
	if (keynb == 65535)
		data->player->is_sprinting = 0;
	return (0);
}

int	close_windows(t_data *data)
{
	exit_and_free(EXIT_SUCCESS, data);
	return (0);
}

int	mouse_manager(int x, int y, t_data *data)
{
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	if (x == SCREEN_W / 2 && y == SCREEN_H / 2)
		return (0);
	if (x >= SCREEN_W / 2)
		rotate_mouse(data, 1);
	else
		rotate_mouse(data, 0);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, SCREEN_W / 2, SCREEN_H / 2);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:40:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:20:21 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, double move_x, double move_y)
{
	int	map_x;
	int	map_y;
	int	new_x;
	int	new_y;

	new_x = roundf(data->player->co.co_x + move_x);
	new_y = roundf(data->player->co.co_y + move_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	if (map_x > (int)data->amount_c || map_y > (int)data->amount_l
		- (int)data->l_map_start || map_x < 0 || map_y < 0)
		return ;
	if (data->map_2d[map_y][map_x] != 1
		&& data->map_2d[map_y][data->player->co.co_x / TILE_SIZE] != 1
		&& data->map_2d[data->player->co.co_y / TILE_SIZE][map_x] != 1)
	{
		data->player->co.co_x = new_x;
		data->player->co.co_y = new_y;
	}
}

void	rotate_player(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_KEY;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_KEY;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	rotate_mouse(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->player->angle += SENSI_MOUSE;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else
	{
		data->player->angle -= SENSI_MOUSE;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

void	manager_player(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	if (data->player->rot_flag == 1)
		rotate_player(data, 1);
	if (data->player->rot_flag == -1)
		rotate_player(data, 0);
	if (data->player->lr_flag == 1)
	{
		move_x = -sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->lr_flag == -1)
	{
		move_x = sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = -cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->ud_flag == 1)
	{
		move_x = cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	if (data->player->ud_flag == -1)
	{
		move_x = -cos(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
		move_y = -sin(data->player->angle) * (data->player->speed
				+ data->player->is_sprinting);
	}
	move_player(data, move_x, move_y);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:58:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 11:36:03 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_plafond_sol(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_H)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->ceiling->r,
				data->ceiling->g, data->ceiling->b));
	i = 0;
	while (i < top_pix)
		my_mlx_pixel_put(data, ray, i++, create_trgb(255, data->floor->r,
				data->floor->g, data->floor->b));
}

int	get_color(t_data *data, int flag)
{
	data->ray->angle = nor_angle(data->ray->angle);
	if (flag == 0)
	{
		if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xFF0000FF); // east wall
	}
	if (data->ray->is_door == 1)
		return (0xAAA32AFF);
	else
	{
		if (data->ray->angle > 0 && data->ray->angle < M_PI)
			return (0x0000FFFF); // south wall
		else
			return (0xFFFF00FF); // north wall
	}
}

void	draw_wall(t_data *data, int ray, int top_pix, int bot_pix)
{
	int	color;

	color = get_color(data, data->ray->inter_h);
	while (top_pix < bot_pix)
	{
		my_mlx_pixel_put(data, ray, top_pix, color);
		top_pix++;
	}
}

void	render_wall(t_data *data, int ray)
{
	double	wall_h;
	double	top_pix;
	double	bot_pix;

	data->ray->distance *= cos(nor_angle(data->ray->angle
				- data->player->angle));
	wall_h = (TILE_SIZE / data->ray->distance) * ((SCREEN_W / 2)
			/ tan(data->player->fov / 2));
	bot_pix = (SCREEN_H / 2) + (wall_h / 2);
	top_pix = (SCREEN_H / 2) - (wall_h / 2);
	if (bot_pix > SCREEN_H)
		bot_pix = SCREEN_H;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(data, ray, top_pix, bot_pix);
	draw_plafond_sol(data, ray, top_pix, bot_pix);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 03:48:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 11:21:19 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
		dst = data->img->addr + (y * data->img->line_length + x
				* (data->img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_texture	*search_texture(t_data *data, char *identifier)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (ft_strcmp(identifier, current->identifier) == 0)
			return (current);
		current = current->next;
	}
	return (current);
}

t_texture	*get_texture(t_data *data, int i)
{
	if (i == 0)
	{
		if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
			return (search_texture(data, ID_EA));
		else
			return (search_texture(data, ID_WE));
	}
	else
	{
		if (data->ray->angle > 0 && data->ray->angle < M_PI)
			return (search_texture(data, ID_SO));
		else
			return (search_texture(data, ID_NO));
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:32:42 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:14:49 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_data *data)
{
	data->player->co.co_x = data->start_player_pos.co_x * TILE_SIZE + TILE_SIZE
		/ 2;
	data->player->co.co_y = data->start_player_pos.co_y * TILE_SIZE + TILE_SIZE
		/ 2;
	if (data->p_id == 11)
		data->player->angle = (M_PI * 3 / 2);
	if (data->p_id == 12)
		data->player->angle = M_PI / 2;
	if (data->p_id == 13)
		data->player->angle = 0;
	if (data->p_id == 14)
		data->player->angle = M_PI;
	data->player->fov = (FOV * M_PI) / 180;
	data->player->speed = START_PLAYER_SPEED;
}

void	start_game(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->ray = ft_calloc(1, sizeof(t_rayon));
	init_player(data);
	mlx_loop_hook(data->mlx_ptr, loop_render_game, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, mouse_manager,
		data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &close_windows,
		data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &press_manager, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &release_manager, data);
	mlx_loop(data->mlx_ptr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:26:02 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 13:39:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief - Libère un objet spécifique géré par le garbage collector.
 *  Sinon,il est retiré de la liste et libéré.
 *
 Si l'objet n'est pas trouvé dans la liste des objets gérés,
 il est simplement libéré.
 * @param garbage: Un pointeur vers la structure du garbage collector.
 * @param content: Un pointeur vers l'objet à libérer.
 *
 */
void	destroy(t_garbage *garbage, void *content)
{
	t_to_destroy	*current;

	if (!garbage)
		return ;
	if (!is_in_garbage(garbage, content))
	{
		free(content);
		return ;
	}
	current = garbage->first;
	while (current->ptr_destroy != content)
		current = current->next;
	if (current->before)
		current->before->next = current->next;
	else
		garbage->first = current->next;
	if (current->next)
		current->next->before = current->before;
	(free(current->ptr_destroy), free(current));
}

/**
 * @brief Libère tous les objets gérés par le garbage collector.
 *
 * Parcourt la liste des objets gérés et les libère tous,
	ainsi que la structure du garbage collector elle-même.
 * @param garbage: Un pointeur vers la structure du garbage collector.
 *
 */
void	destroy_all(t_garbage *garbage)
{
	t_to_destroy	*current;
	t_to_destroy	*next;

	if (garbage)
	{
		if (!garbage->first)
		{
			free(garbage);
			return ;
		}
		current = garbage->first;
		while (current)
		{
			next = current->next;
			free(current->ptr_destroy);
			free(current);
			current = next;
		}
	}
	free(garbage);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:26:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 13:39:31 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  Initialise une nouvelle structure de garbage collector.
 *

	* Alloue de la mémoire pour une nouvelle structure t_garbage et initialise
		ses membres.
 *
 * Retourne un pointeur vers la nouvelle structure t_garbage,
	ou NULL en cas d'échec d'allocation.
 */
t_garbage	*init_garbage(void)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->first = NULL;
	new->total_alloc = 0;
	new->total_free = 0;
	return (new);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:19:59 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 13:39:34 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief
	- Alloue de la mémoire et l'ajoute à la liste des objets gérés par le
	garbage collector.
 * @param size: La taille de la mémoire à allouer.
	Si size est égal à DESTROY_TOKEN,
	le garbage collector est réinitialisé.
 *
 * Retourne un pointeur vers la mémoire allouée,
	ou NULL en cas d'échec ou si size est DESTROY_TOKEN.
 */
void	*gc_malloc(long int size)
{
	static t_garbage	*garbage;
	void				*ptr;

	if (!garbage && size != DESTROY_TOKEN)
		garbage = init_garbage();
	if (size == DESTROY_TOKEN)
	{
		garbage = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	push_to_garbage(garbage, ptr, size);
	if (!garbage->total_alloc)
		gc_free(garbage);
	garbage->total_alloc++;
	return (ptr);
}

/**
 * @brief - Libère la mémoire gérée par le garbage collector.

	* @param ptr: Un pointeur vers la mémoire à libérer.
 *
 * Si ptr est égal à DESTROY_PTR,
	tous les objets gérés par le garbage collector sont libérés et
	le garbage collector est réinitialisé.
 * Si ptr est NULL, la fonction ne fait rien.
 */
void	gc_free(void *ptr)
{
	static int			i = DESTROY_TOKEN;
	static t_garbage	*garbage;

	if (ptr == DESTROY_PTR)
	{
		i = DESTROY_TOKEN;
		destroy_all(garbage);
		garbage = gc_malloc(DESTROY_TOKEN);
		return ;
	}
	if (!ptr)
		return ;
	if (i == DESTROY_TOKEN)
	{
		garbage = ptr;
		i++;
		return ;
	}
	destroy(garbage, ptr);
	garbage->total_free++;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:25:13 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 13:39:37 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_to_destroy	*push_to_garbage(t_garbage *garbage, void *ptr, long int size)
{
	t_to_destroy	*new;
	t_to_destroy	*current;

	new = malloc(sizeof(t_to_destroy));
	if (!new)
		return (NULL);
	new->ptr_destroy = ptr;
	new->before = NULL;
	if (!garbage->first)
	{
		garbage->first = new;
	}
	else
	{
		current = garbage->first;
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
	new->next = NULL;
	new->size = size;
	return (new);
}

int	is_in_garbage(t_garbage *garbage, void *content)
{
	t_to_destroy	*current;

	current = garbage->first;
	while (current)
	{
		if (current->ptr_destroy == content)
			return (1);
		current = current->next;
	}
	return (0);
}

void	gc_free_2d(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		gc_free(split[i++]);
	gc_free(split);
	split = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:32:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/05 14:03:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls(t_data *data)
{
	const size_t	nb_line = data->amount_l - data->l_map_start;
	size_t			i;

	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[0][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
		i++;
	}
	i = 0;
	while (i < data->amount_c)
	{
		if (data->map_2d[nb_line][i] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
		i++;
	}
	i = 0;
	while (i < nb_line)
	{
		if (data->map_2d[i][0] != 1 || data->map_2d[i][data->amount_c - 1] != 1)
			free_and_exit(EXIT_FAILURE, WALL_ERR, data);
		i++;
	}
}

void	check_player(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (i < data->amount_l - data->l_map_start)
	{
		j = 0;
		while (j < data->amount_c)
		{
			if (data->map_2d[i][j] == 11 || data->map_2d[i][j] == 12
				|| data->map_2d[i][j] == 13 || data->map_2d[i][j] == 14)
			{
				data->start_player_pos.co_x = j;
				data->start_player_pos.co_y = i;
				data->p_id = data->map_2d[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count < 1)
		free_and_exit(EXIT_FAILURE, NO_P_ERR, data);
	if (count > 1)
		free_and_exit(EXIT_FAILURE, TOO_P_ERR, data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:23:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 19:57:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_colors(t_data *data, t_texture *current)
{
	char	**rgb_splitted;
	char	*line_without_space;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	if (ft_strcmp(current->identifier, ID_C) == 0 && !data->ceiling)
		data->ceiling = gc_malloc(sizeof(t_rgb));
	if (ft_strcmp(current->identifier, ID_F) == 0 && !data->floor)
		data->floor = gc_malloc(sizeof(t_rgb));
	if ((ft_strcmp(current->identifier, ID_C) == 0 && !data->ceiling)
		|| (ft_strcmp(current->identifier, ID_F) == 0 && !data->floor))
		handle_malloc_error("parse colors", data);
	line_without_space = gc_malloc(ft_strlen(current->path) + 1);
	if (!line_without_space)
		handle_malloc_error("parse colors", data);
	while (*current->path)
	{
		if (*current->path != ' ')
			line_without_space[i++] = *current->path;
		current->path++;
	}
	line_without_space[i] = '\0';
	rgb_splitted = ft_split(line_without_space, ',');
	if (!rgb_splitted)
		handle_malloc_error("parse colors", data);
	if (!rgb_splitted[0] || !rgb_splitted[1] || !rgb_splitted[2])
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	if (ft_strcmp(rgb_splitted[0], "\n") == 0 || ft_strcmp(rgb_splitted[1],
			"\n") == 0 || ft_strcmp(rgb_splitted[2], "\n") == 0)
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	r = ft_atoi(rgb_splitted[0]);
	g = ft_atoi(rgb_splitted[1]);
	b = ft_atoi(rgb_splitted[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_and_exit(EXIT_FAILURE, RGB_ERR, data);
	gc_free(line_without_space);
	if (ft_strcmp(current->identifier, ID_C) == 0)
	{
		data->ceiling->r = r;
		data->ceiling->g = g;
		data->ceiling->b = b;
	}
	if (ft_strcmp(current->identifier, ID_F) == 0)
	{
		data->floor->r = r;
		data->floor->g = g;
		data->floor->b = b;
	}
	gc_free_2d(rgb_splitted);
}

void	check_color(t_data *data)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (ft_strcmp(current->identifier, ID_C) == 0
			|| ft_strcmp(current->identifier, ID_F) == 0)
			parse_colors(data, current);
		current = current->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:22 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 11:15:28 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	unknown_char(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == WALL || str[i] == FLOOR || str[i] == PLAYER_E
			|| str[i] == PLAYER_N || str[i] == PLAYER_S || str[i] == PLAYER_W
			|| str[i] == DOOR || str[i] == EMPTY || str[i] == ENDOF)
			i++;
		else
		{
			close(data->fd);
			free_and_exit(EXIT_FAILURE, "Unknown character in the map", data);
		}
	}
}

static void	allocate_line(char *line, t_data *data, int i)
{
	size_t	index;
	size_t	j;

	j = 0;
	index = 0;
	data->map_2d[i] = gc_malloc(data->amount_c * (sizeof(int)));
	if (!data->map_2d[i])
		handle_malloc_error("parse 2d map", data);
	while (j < data->amount_c)
	{
		data->map_2d[i][j] = 1;
		j++;
	}
	while (line[index] && index < data->amount_c)
	{
		if (line[index] == FLOOR)
			data->map_2d[i][index] = 0;
		else if (line[index] == PLAYER_N)
			data->map_2d[i][index] = 11;
		else if (line[index] == PLAYER_S)
			data->map_2d[i][index] = 12;
		else if (line[index] == PLAYER_E)
			data->map_2d[i][index] = 13;
		else if (line[index] == PLAYER_W)
			data->map_2d[i][index] = 14;
		else if (line[index] == DOOR)
			data->map_2d[i][index] = 42;
		else
			data->map_2d[i][index] = 1;
		index++;
	}
}

void	create_2dmap(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		unknown_char(line, data);
		allocate_line(line, data, i);
		gc_free(line);
		line = get_next_line(data->fd);
		i++;
	}
}

void	parse_map(t_data *data, char **av)
{
	const size_t	nb_line = data->amount_l - data->l_map_start;
	size_t			follow_l;
	char			*line;

	follow_l = data->l_map_start - 1;
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, ERR_OPEN, data);
	data->map_2d = gc_malloc((nb_line + 1) * (sizeof(int *)));
	if (!data->map_2d)
		handle_malloc_error("parse 2d map", data);
	while (follow_l)
	{
		line = get_next_line(data->fd);
		gc_free(line);
		follow_l--;
	}
	create_2dmap(data);
	close(data->fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:07:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 20:32:48 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_texture(t_data *data, char *line, char *identifier)
{
	t_texture	*new_node;
	t_texture	*current;

	new_node = gc_malloc(sizeof(t_texture));
	if (!new_node)
		handle_malloc_error("new texture", data);
	new_node->identifier = ft_strdup(identifier);
	if (!new_node->identifier)
		handle_malloc_error("new texture", data);
	new_node->path = ft_strdup(line);
	if (!new_node->path)
		handle_malloc_error("new texture", data);
	new_node->img = NULL;
	new_node->next = NULL;
	if (!data->texture)
	{
		data->texture = new_node;
		return ;
	}
	current = data->texture;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	test_identifier(char *line, t_data *data)
{
	while (*line && is_whitespace(*line))
		line++;
	if (ft_strncmp(line, ID_NO, 3) == 0)
		return (new_texture(data, line + 3, ID_NO), 1);
	else if (ft_strncmp(line, ID_SO, 3) == 0)
		return (new_texture(data, line + 3, ID_SO), 1);
	else if (ft_strncmp(line, ID_EA, 3) == 0)
		return (new_texture(data, line + 3, ID_EA), 1);
	else if (ft_strncmp(line, ID_WE, 3) == 0)
		return (new_texture(data, line + 3, ID_WE), 1);
	else if (ft_strncmp(line, ID_F, 2) == 0)
		return (new_texture(data, line + 2, ID_F), 1);
	else if (ft_strncmp(line, ID_C, 2) == 0)
		return (new_texture(data, line + 2, ID_C), 1);
	return (0);
}

void	start_parse(t_data *data, char **av)
{
	char	*line;
	size_t	nb_elem;
	size_t	count_line;

	count_line = 0;
	nb_elem = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		if (test_identifier(line, data))
			nb_elem++;
		else if (ft_strcmp(line, "\n"))
			break ;
		gc_free(line);
		line = get_next_line(data->fd);
		count_line++;
	}
	data->l_map_start = count_line + 1;
	if (!line)
		(close(data->fd), free_and_exit(EXIT_FAILURE, "No map found", data));
	if (nb_elem < 6 || nb_elem > 6)
		(close(data->fd), free_and_exit(EXIT_FAILURE, "Wrong elements", data));
	data->amount_c = calculate_max_c(data, line) - 1;
	parse_map(data, av);
	(check_walls(data), check_player(data), check_color(data));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:05:15 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/01 07:17:14 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_cub(char *name)
{
	const size_t	len = ft_strlen(name);

	if (name[len - 3] != 'c' || name[len - 2] != 'u' || name[len - 1] != 'b')
		free_and_exit(EXIT_FAILURE, "The map should be .cub map", NULL);
}

size_t	calculate_max_c(t_data *data, char *line)
{
	size_t	max_strlen;

	max_strlen = 0;
	while (line)
	{
		if (max_strlen < ft_strlen(line))
			max_strlen = ft_strlen(line);
		gc_free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	return (max_strlen);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:24:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:01:54 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_data *data)
{
	data->img->img_ptr = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
	data->img->addr = mlx_get_data_addr(data->img->img_ptr,
			&data->img->bits_per_pixel, &data->img->line_length,
			&data->img->endian);
}

void	parse_xpm(t_data *data, t_texture *current)
{
	char	*trimmed_path;

	trimmed_path = ft_strtrim(current->path, "\n\t ");
	gc_free(current->path);
	current->path = trimmed_path;
	current->img = mlx_xpm_file_to_image(data->mlx_ptr, current->path,
			&current->s_x, &current->s_y);
	if (!current->img)
		free_and_exit(EXIT_FAILURE, XPM_FAILED, data);
}

void	check_xpm(t_data *data)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (ft_strcmp(current->identifier, ID_NO) == 0
			|| ft_strcmp(current->identifier, ID_SO) == 0
			|| ft_strcmp(current->identifier, ID_WE) == 0
			|| ft_strcmp(current->identifier, ID_EA) == 0)
			parse_xpm(data, current);
		current = current->next;
	}
}

void	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		free_and_exit(EXIT_FAILURE, MLX_ERROR, data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H, "TQT");
	if (!data->win_ptr)
		free_and_exit(EXIT_FAILURE, WIN_ERROR, data);
	data->img = gc_malloc(sizeof(t_img));
	if (!data->img)
		handle_malloc_error("img mlx", data);
	check_xpm(data);
	init_image(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:25:54 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/05 09:56:43 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_map_parsing(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	width;

	printf("\n=== TEST MAP PARSING ===\n");
	// Affichage de la map avec symboles pour plus de clarté
	i = 0;
	while (i <= data->amount_l - data->l_map_start)
	{
		j = 0;
		width = data->amount_c;
		while (j < width)
		{
			if (data->map_2d[i][j] == 0)
				printf("  "); // FLOOR
			else if (data->map_2d[i][j] == 1)
				printf("🧱"); // WALL
			else if (data->map_2d[i][j] == 11)
				printf("↑ "); // PLAYER_N
			else if (data->map_2d[i][j] == 12)
				printf("↓ "); // PLAYER_S
			else if (data->map_2d[i][j] == 13)
				printf("→ "); // PLAYER_E
			else if (data->map_2d[i][j] == 14)
				printf("← "); // PLAYER_W
			else if (data->map_2d[i][j] == 42)
				printf("🚪"); // DOOR
			else
				printf("❌"); // UNKNOWN
			j++;
		}
		printf("\n");
		i++;
	}
	// Affichage numérique pour debug
	printf("\n=== NUMERIC VALUES ===\n");
	i = 0;
	while (i <= data->amount_l - data->l_map_start)
	{
		j = 0;
		width = data->amount_c;
		while (j < width)
		{
			printf("%2d ", data->map_2d[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	affiche_texture_debug(t_data data)
{
	while (data.texture)
	{
		printf("id:[%s]\npath: %s\n", data.texture->identifier,
			data.texture->path);
		data.texture = data.texture->next;
	}
	printf("line map start: %zu\n", data.l_map_start);
	printf("montant de ligne fichier: %zu\n", data.amount_l);
	printf("Max taille colonne:%zu\n", data.amount_c);
	printf("-------------TEST PLAYER----------------\n");
	printf("start position: %d %d\n", data.start_player_pos.co_x,
		data.start_player_pos.co_y);
	printf("ID de l'orientation:%d\n", data.p_id);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 12:03:07 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_all_mlx(t_data *data)
{
	t_texture	*current;

	current = data->texture;
	while (current)
	{
		if (current->img)
			mlx_destroy_image(data->mlx_ptr, current->img);
		current = current->next;
	}
	if (data->img && data->img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void	free_and_exit(int code, char *message, t_data *data)
{
	ft_fprintf(2, "Error\n");
	ft_fprintf(2, "%s\n", message);
	if (data)
		destroy_all_mlx(data);
	gc_free(DESTROY_PTR);
	exit(code);
}

void	exit_and_free(int code, t_data *data)
{
	if (data)
		destroy_all_mlx(data);
	gc_free(DESTROY_PTR);
	exit(code);
}

void	handle_malloc_error(char *message, t_data *data)
{
	ft_fprintf(2, "Error: malloc failed when allocate for %s\n", message);
	close(data->fd);
	gc_free(DESTROY_PTR);
	exit(EXIT_FAILURE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:18:45 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/07 11:25:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	calculate_l(int fd)
{
	size_t	count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		gc_free(line);
		line = get_next_line(fd);
	}
	return (count);
}

void	init_cub(t_data *data, char **av)
{
	data->texture = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img = NULL;
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, ERR_OPEN, data);
	data->amount_l = calculate_l(data->fd);
	close(data->fd);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		free_and_exit(EXIT_FAILURE, ERR_OPEN, data);
}
