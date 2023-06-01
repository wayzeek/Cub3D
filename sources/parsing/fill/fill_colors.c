/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:43:50 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 12:45:28 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	fill_color(char **color_splitted)
{
	char	**color_splitted2;
	int		color;

	color_splitted2 = ft_split(color_splitted[0], ' ');
	if (!color_splitted2)
		return (-1);
	color = create_trgb(0, ft_atoi(color_splitted2[1]), \
	ft_atoi(color_splitted[1]), ft_atoi(color_splitted[2]));
	free_tab(color_splitted2);
	return (color);
}

int	get_color(char	*line)
{
	char	**color_splitted;
	int		color;

	color_splitted = ft_split(line, ',');
	if (!color_splitted)
		return (printf("Error\n"), -1);
	color = fill_color(color_splitted);
	return (free_tab(color_splitted), color);
}
