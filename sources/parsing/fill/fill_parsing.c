/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:17:44 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 15:33:49 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	fill_floor_ceiling(t_data *data, char *line, int mode)
{
	if (check_error_color(line))
		return (-1);
	if (mode == 'F')
	{
		data->parsing.color_floor = get_color(line);
		if (data->parsing.color_floor == -1)
			return (-1);
	}
	else
	{
		data->parsing.color_ceiling = get_color(line);
		if (data->parsing.color_ceiling == -1)
			return (-1);
	}
	return (0);
}

int	fill_directions(t_data *data, char *line, int mode)
{
	//if (check_error_directions(line))
		//return (-1);
	if (mode == 'N')
	{
		data->parsing.path_texture_north = get_path(line);
		if (data->parsing.path_texture_north == NULL)
			return (-1);
	}
	else if (mode == 'S')
	{
		data->parsing.path_texture_south = get_path(line);
		if (data->parsing.path_texture_south == NULL)
			return (-1);
	}
	else if (mode == 'W')
	{
		data->parsing.path_texture_west = get_path(line);
		if (data->parsing.path_texture_west == NULL)
			return (-1);
	}
	else if (mode == 'E')
	{
		data->parsing.path_texture_east = get_path(line);
		if (data->parsing.path_texture_east == NULL)
			return (-1);
	}
	return (0);
}

int	fill_map(t_data *data, char *line, int map_size, int map_fd)
{
	int	i;

	data->parsing.map = malloc(sizeof(char *) * (map_size + 2));
	if (!data->parsing.map)
		return (printf("Error\n"), -1);
	i = 0;
	while (line)
	{
		data->parsing.map[i] = remove_nl(line);
		if (!data->parsing.map[i])
			return (printf("Error\n"), free(line), -1);
		if (i != 0)
			free(line);
		line = get_next_line(map_fd);
		i++;
	}
	data->parsing.map[i] = NULL;
	free(line);
	if (check_map_error(data->parsing.map) == -1)
		return (-1);
	data->parsing.map_size_width = len_tab(data->parsing.map);
	return (0);
}
