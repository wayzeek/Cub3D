/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:33:03 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 15:41:02 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_map_char(char **map)
{
	int	player_found;
	int	x;
	int	y;

	player_found = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_contains("01NSEW ", map[y][x]))
				return (printf("Error\nMap contains forbidden char !\n"), -1);
			if (ft_contains("NSEW", map[y][x]))
				player_found++;
			x++;
		}
		y++;
	}
	if (player_found != 1)
		return (printf("Error\nMultiple or no spawn points found!\n"), -1);
	return (0);
}

static int	map_has_void(char **map)
{
	int		x;
	int		y;
	char	**full_map;

	y = 1;
	full_map = complete_map(map);
	while (y < len_tab(map) - 1)
	{
		x = 0;
		while (full_map[y][x])
		{
			if (full_map[y][x] == '0' && (full_map[y - 1][x] == '3' \
			|| full_map[y + 1][x] == '3'))
				return (free_tab(full_map), \
				printf("Error\nMap not closed by walls!\n"), -1);
			else if (full_map[y][x] == '0' && (full_map[y][x - 1] == '3' \
			|| full_map[y][x + 1] == '3'))
				return (free_tab(full_map), \
				printf("Error\nMap not closed by walls!\n"), -1);
			x++;
		}
		y++;
	}
	free_tab(full_map);
	return (0);
}

static int	map_has_border(char	**map)
{
	int		i;
	char	*line_no_space;

	i = 0;
	while (map[i])
	{
		line_no_space = remove_spaces(map[i]);
		if (i == 0 || i == len_tab(map) - 1)
		{
			if (check_border(line_no_space) == -1)
				return (free(line_no_space), -1);
		}
		else
		{
			if (line_is_closed(line_no_space) == -1)
				return (free(line_no_space), -1);
		}
		free(line_no_space);
		i++;
	}
	return (0);
}

int	check_map_error(char **map)
{
	if (check_map_char(map) == -1)
		return (-1);
	if (map_has_void(map) == -1)
		return (-1);
	if (map_has_border(map) == -1)
		return (-1);
	return (0);
}
