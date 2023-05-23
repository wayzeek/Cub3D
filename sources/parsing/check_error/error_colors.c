/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:39:44 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:34:57 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_colors(int map_fd)
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
		if (check_line_colors(line) == -1)
			return (-1);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	if (i != 2)
		return (free(line), \
		printf("Error\nNot enough colors parameters !\n"), -1);
	return (free(line), 0);
}

int	check_line_colors(char	*line)
{
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (printf("Error\n"), -1);
	if (len_tab(line_splitted) != 2)
		return (free_tab(line_splitted), \
		printf("Error\nColors not valid!\n"), -1);
	if (!valid_colors_id(line_splitted[0]))
		return (free_tab(line_splitted), \
		printf("Error\nColors ID not valid!\n"), -1);
	if (!valid_rgb(line_splitted[1]))
		return (free_tab(line_splitted), \
		printf("Error\nColors RGB not valid!\n"), -1);
	free_tab(line_splitted);
	return (0);
}
