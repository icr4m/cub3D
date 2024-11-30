/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:24:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 20:57:33 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_xpm(t_data *data, t_texture *current)
{
	char	*newline;

	if ((newline = strchr(current->path, '\n')))
		*newline = '\0';
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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 200, 200, "TQT");
	if (!data->win_ptr)
		free_and_exit(EXIT_FAILURE, WIN_ERROR, data);
	check_xpm(data);
}
