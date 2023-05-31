/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:39:48 by vcart             #+#    #+#             */
/*   Updated: 2023/05/31 10:58:15 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_directions(int map_fd)
{
	char	*line;
	int		i;

	line = get_next_line(map_fd);
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
		if (check_line_directions(line) == -1)
			return (free(line), -1);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	if (i != 4)
		return (free(line), \
		printf("Error\nNot enough or too many directions parameters !\n"), -1);
	return (free(line), 0);
}

int	check_line_directions(char	*line)
{
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (printf("Error\n"), -1);
	if (len_tab(line_splitted) != 2)
		return (free_tab(line_splitted), \
		printf("Error\nDirections not valid!\n"), -1);
	if (!valid_directions_id(line_splitted[0]))
		return (free_tab(line_splitted), \
		printf("Error\nDirections ID not valid!\n"), -1);
	free_tab(line_splitted);
	return (0);
}
