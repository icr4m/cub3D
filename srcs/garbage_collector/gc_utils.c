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
