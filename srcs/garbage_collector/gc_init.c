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
