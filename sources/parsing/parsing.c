/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:54:37 by vcart             #+#    #+#             */
/*   Updated: 2023/06/14 18:40:15 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_and_open_map(char *map_name)
{
	int	map_fd;

	if (!check_extension(map_name))
		return (printf("Error\nWrong map extension\n"), -1);
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (printf("Error\nCan't open map file\n"), -1);
	return (map_fd);
}

static char	*skip_new_line(char *line, int map_fd)
{
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
		if (!line)
			return (NULL);
	}
	return (line);
}

int	get_parsing(t_data *data, char *map_name)
{
	int		map_fd;
	int		map_size;
	char	*line;

	init_parsing(data);
	map_fd = check_and_open_map(map_name);
	if (map_fd == -1)
		return (-1);
	map_size = get_map_size(map_name);
	if (map_size == -1)
		return (-1);
	line = get_next_line(map_fd);
	while (line)
	{
		line = skip_new_line(line, map_fd);
		if (!line)
			return (0);
		if (process_line(data, line, map_size, map_fd) == -1)
			return (free(line), -1);
		free(line);
		line = get_next_line(map_fd);
	}
	return (free(line), 0);
}
