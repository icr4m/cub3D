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
