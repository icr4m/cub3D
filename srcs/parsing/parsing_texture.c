/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:07:01 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 15:44:23 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_unique_textures(t_data *data)
{
	t_texture	*current;
	t_texture	*check;

	current = data->texture;
	while (current)
	{
		check = current->next;
		while (check)
		{
			if (ft_strcmp(current->identifier, check->identifier) == 0)
				(close(data->fd), free_and_exit(EXIT_FAILURE,
						"Duplicate texture identifier", data));
			check = check->next;
		}
		current = current->next;
	}
}

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
	new_node->img = NULL;
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
	while (*line && is_whitespace(*line))
		line++;
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

void	start_parse(t_data *data, char **av)
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
		(gc_free(line), line = get_next_line(data->fd));
		count_line++;
	}
	data->l_map_start = count_line + 1;
	if (!line)
		(close(data->fd), free_and_exit(EXIT_FAILURE, "No map found", data));
	if (nb_elem != 6)
		(close(data->fd), free_and_exit(EXIT_FAILURE, "Wrong elements", data));
	data->amount_c = calculate_max_c(data, line) - 1;
	(new_texture(data, "textures/rendu/DOOR.xpm", ID_DO),
		check_unique_textures(data), parse_map(data, av));
	(check_walls(data), check_player(data), check_color(data));
}
