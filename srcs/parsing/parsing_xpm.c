/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:24:14 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/19 15:36:55 by erwfonta         ###   ########.fr       */
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
	current->pixel_addr = mlx_get_data_addr(current->img, &current->bpp,
			&current->line_lenght, &current->endian);
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
			|| ft_strcmp(current->identifier, ID_EA) == 0
			|| ft_strcmp(current->identifier, ID_DO) == 0)
			parse_xpm(data, current);
		current = current->next;
	}
}

void	init_doors(t_data *data)
{
	int	x;
	int	y;
	int	count;

	// Première passe : compter le nombre de portes
	count = 0;
	y = 0;
	while (y < (int)(data->amount_l - data->l_map_start))
	{
		x = 0;
		while (x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
				count++;
			x++;
		}
		y++;
	}
	// Allouer le tableau de portes
	data->nb_doors = count;
	data->doors = gc_malloc(sizeof(t_doors *) * count);
	if (!data->doors)
		handle_malloc_error("door allocation", data);
	// Deuxième passe : initialiser chaque porte
	count = 0;
	y = 0;
	while (y < (int)(data->amount_l - data->l_map_start))
	{
		x = 0;
		while (x < (int)data->amount_c)
		{
			if (data->map_2d[y][x] == 42)
			{
				data->doors[count] = gc_malloc(sizeof(t_doors));
				if (!data->doors[count])
					handle_malloc_error("door allocation", data);
				data->doors[count]->position = 1;
				data->doors[count]->is_moving = 0;
				data->doors[count]->speed = 0.005; // Ajustez selon vos besoins
				count++;
			}
			x++;
		}
		y++;
	}
}

void	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		free_and_exit(EXIT_FAILURE, MLX_ERROR, data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_W, SCREEN_H,
			"TIG_CUB3D");
	if (!data->win_ptr)
		free_and_exit(EXIT_FAILURE, WIN_ERROR, data);
	data->img = gc_malloc(sizeof(t_img));
	if (!data->img)
		handle_malloc_error("img mlx", data);
	data->img->img_ptr = NULL;
	check_xpm(data);
	init_image(data);
	init_doors(data);
}
