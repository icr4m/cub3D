/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:44:18 by ijaber            #+#    #+#             */
/*   Updated: 2025/01/20 17:54:12 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	*init_rgb_struct(t_data *data, char *identifier)
{
	t_rgb	*rgb;

	rgb = NULL;
	if (ft_strcmp(identifier, ID_C) == 0 && !data->ceiling)
		data->ceiling = gc_malloc(sizeof(t_rgb));
	if (ft_strcmp(identifier, ID_F) == 0 && !data->floor)
		data->floor = gc_malloc(sizeof(t_rgb));
	if ((ft_strcmp(identifier, ID_C) == 0 && !data->ceiling)
		|| (ft_strcmp(identifier, ID_F) == 0 && !data->floor))
		handle_malloc_error("parse colors", data);
	if (ft_strcmp(identifier, ID_C) == 0)
		rgb = data->ceiling;
	else
		rgb = data->floor;
	return (rgb);
}

char	*remove_spaces(t_data *data, char *str)
{
	char	*clean_str;
	int		i;

	i = 0;
	clean_str = gc_malloc(ft_strlen(str) + 1);
	if (!clean_str)
		handle_malloc_error("parse colors", data);
	while (*str)
	{
		if (*str != ' ')
			clean_str[i++] = *str;
		str++;
	}
	clean_str[i] = '\0';
	return (clean_str);
}

void	check_rgb_values(char **rgb_splitted, t_data *data)
{
	if (!rgb_splitted[0] || !rgb_splitted[1] || !rgb_splitted[2])
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	if (ft_strcmp(rgb_splitted[0], "\n") == 0 || ft_strcmp(rgb_splitted[1],
			"\n") == 0 || ft_strcmp(rgb_splitted[2], "\n") == 0)
		free_and_exit(EXIT_FAILURE, RGB_FORMAT_ERR, data);
	rgb_splitted[2][ft_strlen(rgb_splitted[2]) - 1] = '\0';
	if (!ft_is_numeric(rgb_splitted[0]) || !ft_is_numeric(rgb_splitted[1])
		|| !ft_is_numeric(rgb_splitted[2]))
		free_and_exit(EXIT_FAILURE, RGB_CHAR_ERR, data);
}

void	set_rgb_values(t_rgb *rgb, char **rgb_splitted, t_data *data)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb_splitted[0]);
	g = ft_atoi(rgb_splitted[1]);
	b = ft_atoi(rgb_splitted[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_and_exit(EXIT_FAILURE, RGB_ERR, data);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}
