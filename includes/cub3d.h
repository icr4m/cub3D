/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/12/04 10:00:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# include <math.h>
//
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
//
# include "../includes/struct.h"
//
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
//
# include "../includes/exec.h"
# include "../includes/garbage_collector.h"
# include "../includes/parsing.h"
# include "../includes/utils.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"

# define ID_NO "NO "
# define ID_SO "SO "
# define ID_WE "WE "
# define ID_EA "EA "
# define ID_F "F "
# define ID_C "C "

# define WALL '1'
# define FLOOR '0'
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_E 'E'
# define PLAYER_W 'W'
# define DOOR 'D'
# define EMPTY ' '
# define ENDOF '\n'

# define FAILED_ALLOC "Malloc failed."
# define WALL_ERR "Map must be surrounded by walls."
# define NO_P_ERR "No player start found"
# define TOO_P_ERR "Too much player start found"
# define RGB_ERR "RGB values must be between 0 and 255"
# define RGB_FORMAT_ERR "RGB format should be R,G,B"
# define XPM_FAILED "Problem with xpm files"
# define MLX_ERROR "Failed to initialize mlx"
# define WIN_ERROR "Failed to create a window with mlx"

# define FOV 60
# define TILE_SIZE 30
# define SCREEN_W 1024
# define SCREEN_H 640
# define SENSI_ROTA 0.05
# define PLAYER_SPEED 6

#endif