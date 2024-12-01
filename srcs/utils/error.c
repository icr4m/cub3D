/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/30 21:48:01 by ijaber           ###   ########.fr       */
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

void	handle_malloc_error(char *message, t_data *data)
{
	ft_fprintf(2, "Error: malloc failed when allocate for %s\n", message);
	close(data->fd);
	gc_free(DESTROY_PTR);
	exit(EXIT_FAILURE);
}
