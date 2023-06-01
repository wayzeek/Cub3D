/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:54:19 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 20:28:45 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_only_num(char	*color)
{
	while (*color)
	{
		if (!ft_contains("0123456789 \n", *color))
			return (0);
		color++;
	}
	return (1);
}

static int	check_color_splitted(char *color, int i)
{
	char	**color_splitted2;

	color_splitted2 = ft_split(color, ' ');
	if (!color_splitted2)
		return (printf("Error\n"), 0);
	if (len_tab(color_splitted2) == 2 && i == 0)
	{
		if (!check_only_num(color_splitted2[1]))
			return (free_tab(color_splitted2), 0);
		if (ft_atoi(color_splitted2[1]) < 0 || \
		ft_atoi(color_splitted2[1]) > 255)
			return (free_tab(color_splitted2), 0);
	}
	else if (len_tab(color_splitted2) != 1 && i == 1)
		return (free_tab(color_splitted2), 0);
	else
	{
		if (!check_only_num(color_splitted2[0]))
			return (free_tab(color_splitted2), 0);
		if (ft_atoi(color_splitted2[0]) < 0 || \
		ft_atoi(color_splitted2[0]) > 255)
			return (free_tab(color_splitted2), 0);
	}
	free_tab(color_splitted2);
	return (1);
}

static int	valid_rgb(char	*str)
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

int	check_error_color(char *line)
{
	char	**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (!line_splitted)
		return (printf("Error\n"), 1);
	if (!valid_rgb(line))
		return (free_tab(line_splitted), \
		printf("Error\nColors RGB not valid!\n"), 1);
	free_tab(line_splitted);
	return (0);
}