/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:02:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 16:39:38 by ijaber           ###   ########.fr       */
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
