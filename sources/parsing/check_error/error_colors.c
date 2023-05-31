/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:39:44 by vcart             #+#    #+#             */
/*   Updated: 2023/05/31 13:35:25 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_color_splitted(char *color, int i)
{
	char	**color_splitted2;

	color_splitted2 = ft_split(color, ' ');
	if (!color_splitted2)
		return (printf("Error\n"), 0);
	if (len_tab(color_splitted2) == 2 && i == 0)
	{
		if (ft_atoi(color_splitted2[1]) < 0 || \
		ft_atoi(color_splitted2[1]) > 255)
			return (free_tab(color_splitted2), 0);
	}
	else if (len_tab(color_splitted2) != 1 && i == 1)
		return (free_tab(color_splitted2), 0);
	else
	{
		if (ft_atoi(color_splitted2[0]) < 0 || \
		ft_atoi(color_splitted2[0]) > 255)
			return (free_tab(color_splitted2), 0);
	}
	free_tab(color_splitted2);
	return (1);
}

int	valid_rgb(char	*str)
{
	char	**color_splitted;
	int		i;

	color_splitted = ft_split(str, ',');
	if (!color_splitted)
		return (printf("Error\n"), 0);
	if (len_tab(color_splitted) != 3)
		return (free_tab(color_splitted), 0);
	i = 0;
	while (color_splitted[i])
	{
		if (!check_color_splitted(color_splitted[i], i))
			return (free_tab(color_splitted), 0);
		i++;
	}
	return (free_tab(color_splitted), 1);
}

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
			return (free(line), -1);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	if (i != 2)
		return (free(line), \
		printf("Error\nNot enough or too many colors parameters !\n"), -1);
	return (free(line), 0);
}

int	check_line_colors(char	*line)
{
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (printf("Error\n"), -1);
	if (!valid_colors_id(line_splitted[0]))
		return (free_tab(line_splitted), \
		printf("Error\nColors ID not valid!\n"), -1);
	if (!valid_rgb(line))
		return (free_tab(line_splitted), \
		printf("Error\nColors RGB not valid!\n"), -1);
	free_tab(line_splitted);
	return (0);
}
