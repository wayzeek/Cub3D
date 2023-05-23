/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:29:33 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:35:35 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_mode(int map_fd)
{
	char	*line;
	char	**line_splitted;

	line = go_to_beginning_text(map_fd);
	while (line)
	{
		if (line[0] == '\n')
			break ;
		line_splitted = ft_split(line, ' ');
		if (!line_splitted)
			return (free(line), -1);
		if (check_mode(line_splitted) == 1)
			return (free_tab(line_splitted), free(line), 1);
		else if (check_mode(line_splitted) == 2)
			return (free_tab(line_splitted), free(line), 2);
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (free(line), 0);
}

int	check_parsing_error(char *map_name, int map_size, int mode)
{
	int	map_fd;

	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (-1);
	if (mode == 1)
	{
		if (check_directions(map_fd) == -1)
			return (-1);
		if (check_colors(map_fd) == -1)
			return (-1);
	}
	else if (mode == 2)
	{
		if (check_colors(map_fd) == -1)
			return (-1);
		if (check_directions(map_fd) == -1)
			return (-1);
	}
	else
		return (printf(".map file not complete !\n"), -1);
	if (check_map(map_fd, map_size) == -1)
		return (-1);
	close(map_fd);
	return (0);
}

int	get_parsing(t_parsing	*parsing, char	*map_name)
{
	int			map_size;
	int			map_fd;
	int			mode;

	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (printf("Error\nMap file not found\n"), -1);
	map_size = get_map_size(map_fd);
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (-1);
	mode = get_mode(map_fd);
	if (mode == -1)
		return (-1);
	if (check_parsing_error(map_name, map_size, mode) == -1)
		return (-1);
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		return (-1);
	if (exec_mode(parsing, map_fd, mode) == -1)
		return (-1);
	if (get_map(parsing, map_fd, map_size) == -1)
		return (free_textures(parsing), free(parsing), -1);
	close(map_fd);
	return (0);
}
