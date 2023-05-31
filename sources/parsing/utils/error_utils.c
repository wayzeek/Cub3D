/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:31:26 by vcart             #+#    #+#             */
/*   Updated: 2023/05/31 13:40:17 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	valid_directions_id(char *str)
{
	if (!ft_strcmp(str, "NO"))
		return (1);
	if (!ft_strcmp(str, "SO"))
		return (1);
	if (!ft_strcmp(str, "WE"))
		return (1);
	if (!ft_strcmp(str, "EA"))
		return (1);
	return (0);
}

int	valid_colors_id(char *str)
{
	if (!ft_strcmp(str, "F"))
		return (1);
	if (!ft_strcmp(str, "C"))
		return (1);
	return (0);
}

int	fill_each_color(t_parsing *parsing, char **color_splitted, int i)
{
	char	**color_splitted2;
	char	mode;

	color_splitted2 = ft_split(color_splitted[i], ' ');
	if (!color_splitted2)
		return (-1);
	mode = color_splitted2[0][0];
	if (mode == 'F')
	{
		parsing->color_floor = create_trgb(0, ft_atoi(color_splitted2[1]), \
		ft_atoi(color_splitted[1]), ft_atoi(color_splitted[2]));
	}
	if (mode == 'C')
	{
		parsing->color_ceiling = create_trgb(0, ft_atoi(color_splitted2[1]) \
		, ft_atoi(color_splitted[1]), ft_atoi(color_splitted[2]));
	}
	free_tab(color_splitted2);
	return (0);
}

char	*complete_line(char	*str, int size)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(sizeof(char) * (size + 1));
	while (str[i])
	{
		if (str[i] == ' ')
			result[i] = '3';
		else
			result[i] = str[i];
		i++;
	}
	while (i < size)
	{
		result[i] = '3';
		i++;
	}
	result[i] = 0;
	return (result);
}
