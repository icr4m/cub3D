/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:31 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 17:25:27 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
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

#endif