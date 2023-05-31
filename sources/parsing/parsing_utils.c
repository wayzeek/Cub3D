/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:15:28 by vcart             #+#    #+#             */
/*   Updated: 2023/05/31 13:32:29 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_mode(char **line_splitted)
{
	if (!ft_strcmp(line_splitted[0], "NO") \
	|| !ft_strcmp(line_splitted[0], "SO") \
	|| !ft_strcmp(line_splitted[0], "EA") \
	|| !ft_strcmp(line_splitted[0], "WE"))
		return (1);
	else if (!ft_strcmp(line_splitted[0], "F") \
	|| !ft_strcmp(line_splitted[0], "C"))
		return (2);
	return (free_tab(line_splitted), 0);
}

int	exec_mode(t_parsing *parsing, int map_fd, int mode)
{
	if (mode == 1)
	{
		if (get_textures(parsing, map_fd) == -1)
			return (-1);
		if (get_colors(parsing, map_fd) == -1)
			return (free_textures(parsing), -1);
	}
	if (mode == 2)
	{
		if (get_colors(parsing, map_fd) == -1)
			return (-1);
		if (get_textures(parsing, map_fd) == -1)
			return (-1);
	}
	return (0);
}

int	fill_textures(char *line, t_parsing *parsing)
{
	char	**line_splitted;

	line[ft_strlen(line) - 1] = '\0';
	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (-1);
	if (!ft_strcmp(line_splitted[0], "NO"))
		parsing->path_texture_north = ft_strdup(line_splitted[1]);
	else if (!ft_strcmp(line_splitted[0], "SO"))
		parsing->path_texture_south = ft_strdup(line_splitted[1]);
	else if (!ft_strcmp(line_splitted[0], "WE"))
		parsing->path_texture_west = ft_strdup(line_splitted[1]);
	else if (!ft_strcmp(line_splitted[0], "EA"))
		parsing->path_texture_east = ft_strdup(line_splitted[1]);
	free(line);
	free_tab(line_splitted);
	return (0);
}

int	fill_colors(char *line, t_parsing *parsing)
{
	char	**color_splitted;
	int		i;

	color_splitted = ft_split(line, ',');
	if (!color_splitted)
		return (printf("Error\n"), -1);
	i = 0;
	while (color_splitted[i])
	{
		if (fill_each_color(parsing, color_splitted, i) == -1)
			return (printf("Error\n"), -1);
		i++;
	}
	return (free_tab(color_splitted), 1);
}

char	**fill_map(char	*line, int map_size, int map_fd)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (map_size + 2));
	if (!map)
		return (NULL);
	while (line)
	{
		if (line[0] == '\n')
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i] = line;
		line = get_next_line(map_fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}
