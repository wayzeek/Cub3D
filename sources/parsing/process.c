/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:20:06 by vcart             #+#    #+#             */
/*   Updated: 2023/06/14 18:34:06 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	process_floor(t_data *data, char *line)
{
	if (data->parsing.color_floor != -1)
		return (printf("Error\nFloor color already filled !\n"), -1);
	if (fill_floor_ceiling(data, line, 'F') == -1)
		return (-1);
	return (0);
}

static int	process_ceiling(t_data *data, char *line)
{
	if (data->parsing.color_ceiling != -1)
		return (printf("Error\nCeiling color already filled !\n"), -1);
	if (fill_floor_ceiling(data, line, 'C') == -1)
		return (-1);
	return (0);
}

static int	process_directions(t_data *data, char *line, char dir)
{
	if (fill_directions(data, line, dir) == -1)
		return (-1);
	return (0);
}

static int	process_map(t_data *data, char *line, int map_size, int map_fd)
{
	if (parsing_is_filled(data) && data->parsing.map == NULL)
	{
		if (fill_map(data, line, map_size, map_fd) == -1)
			return (-1);
		return (0);
	}
	else
		return (printf("Error\nMap is not in last position \
or missing parameters!\n"), -1);
}

int	process_line(t_data *data, char *line, int map_size, int map_fd)
{
	int	index;

	index = get_index_first_char(line);
	if (line[index] == 'F' && line[index + 1] == ' ')
		return (process_floor(data, line));
	else if (line[index] == 'C' && line[index + 1] == ' ')
		return (process_ceiling(data, line));
	else if (line[index] == 'N' && line[index + 1] == 'O')
		return (process_directions(data, line, 'N'));
	else if (line[index] == 'S' && line[index + 1] == 'O')
		return (process_directions(data, line, 'S'));
	else if (line[index] == 'W' && line[index + 1] == 'E')
		return (process_directions(data, line, 'W'));
	else if (line[index] == 'E' && line[index + 1] == 'A')
		return (process_directions(data, line, 'E'));
	else if (line[index] == '1' || line[index] == '0')
		return (process_map(data, line, map_size, map_fd));
	else
		return (printf("Error\nInvalid identifier !\n"), -1);
}
