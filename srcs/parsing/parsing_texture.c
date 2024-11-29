/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:07:01 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/29 18:58:36 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_texture(t_data *data, char *line, char *identifier)
{
	t_texture	*new_node;
	t_texture	*current;

	new_node = gc_malloc(sizeof(t_texture));
	if (!new_node)
		handle_malloc_error("new texture", data);
	new_node->identifier = ft_strdup(identifier);
	if (!new_node->identifier)
		handle_malloc_error("new texture", data);
	new_node->path = ft_strdup(line);
	if (!new_node->path)
		handle_malloc_error("new texture", data);
	new_node->next = NULL;
	if (!data->texture)
	{
		data->texture = new_node;
		return ;
	}
	current = data->texture;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	test_identifier(char *line, t_data *data)
{
	if (ft_strncmp(line, ID_NO, 3) == 0)
		return (new_texture(data, line + 3, ID_NO), 1);
	else if (ft_strncmp(line, ID_SO, 3) == 0)
		return (new_texture(data, line + 3, ID_SO), 1);
	else if (ft_strncmp(line, ID_EA, 3) == 0)
		return (new_texture(data, line + 3, ID_EA), 1);
	else if (ft_strncmp(line, ID_WE, 3) == 0)
		return (new_texture(data, line + 3, ID_WE), 1);
	else if (ft_strncmp(line, ID_F, 2) == 0)
		return (new_texture(data, line + 2, ID_F), 1);
	else if (ft_strncmp(line, ID_C, 2) == 0)
		return (new_texture(data, line + 2, ID_C), 1);
	return (0);
}

void	parse_elements(t_data *data)
{
	char	*line;
	size_t	nb_elem;
	size_t	count_line;

	count_line = 0;
	nb_elem = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		if (test_identifier(line, data))
			nb_elem++;
		else if (ft_strcmp(line, "\n"))
			break ;
		line = get_next_line(data->fd);
		count_line++;
	}
	data->l_map_start = count_line + 1;
	if (nb_elem < 6 || nb_elem > 6)
		free_and_exit(EXIT_FAILURE, "Wrong elements");
}
