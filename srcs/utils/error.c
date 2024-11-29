/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 23:06:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_exit(int code, char *message)
{
	ft_fprintf(2, "Error\n");
	ft_fprintf(2, "%s\n", message);
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
