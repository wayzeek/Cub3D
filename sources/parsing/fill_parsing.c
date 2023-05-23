/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:12:55 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 12:35:54 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_map(t_parsing *parsing, int map_fd, int map_size)
{
	char	*line;
	char	**map;

	line = get_next_line(map_fd);
	if (!line)
		return (-1);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	map = fill_map(line, map_size, map_fd);
	if (!map)
		return (-1);
	if (map_is_closed(map) == -1)
		return (free_tab(map), -1);
	parsing->map = map;
	return (0);
}

int	get_colors(t_parsing *parsing, int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	if (!line)
		return (-1);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		if (line[0] == '\n')
			break ;
		if (fill_colors(line, parsing) == -1)
			return (-1);
		line = get_next_line(map_fd);
		if (!line)
			return (-1);
	}
	free(line);
	return (0);
}

int	get_textures(t_parsing *parsing, int map_fd)
{
	char	*line;
	int		i;

	line = get_next_line(map_fd);
	if (!line)
		return (-1);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	i = 0;
	while (line)
	{
		if (line[0] == '\n')
			break ;
		if (fill_textures(line, parsing) == -1)
			return (-1);
		line = get_next_line(map_fd);
		if (!line)
			return (-1);
		i++;
	}
	free(line);
	return (0);
}

char	*go_to_beginning_text(int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	return (line);
}
