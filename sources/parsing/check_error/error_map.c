/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:39:50 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:35:10 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_map(int map_fd, int size)
{
	int		i;
	char	*line;
	int		position;

	line = get_next_line(map_fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	i = 0;
	position = 0;
	while (line)
	{
		if (line[0] == '\n')
			break ;
		if (check_each_line(line, i, size, position) == -1)
			return (-1);
		line = get_next_line(map_fd);
		i++;
	}
	return (free(line), 0);
}

int	check_line_map(char	*line)
{
	int	position;

	position = is_ok_for_map(line);
	if (position == -1)
		return (free(line), \
		printf("Error\nForbidden character in map!\n"), -40);
	if (line_is_closed(line) == -1)
		return (free(line), -40);
	return (position);
}

int	check_border(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (free(line), printf("Error\nMap not closed by walls!\n"), -1);
		i++;
	}
	return (0);
}

int	line_is_closed(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[0] != '1' || line[len - 1] != '1')
		return (printf("Error\nMap not closed by walls!\n"), -1);
	return (0);
}

int	map_is_closed(char	**map)
{
	int		x;
	int		y;
	char	**full_map;

	y = 1;
	full_map = complete_map(map);
	while (y < len_tab(map))
	{
		x = 0;
		while (full_map[y][x])
		{
			if (full_map[y][x] == '0' && (full_map[y - 1][x] == '3' \
			|| full_map[y + 1][x] == '3'))
				return (free_tab(full_map), \
				printf("Error\nMap not closed by walls!\n"), -1);
			x++;
		}
		y++;
	}
	free_tab(full_map);
	return (0);
}
