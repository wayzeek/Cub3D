/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:31:26 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:35:18 by vcart            ###   ########.fr       */
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
		if (ft_atoi(color_splitted[i]) < 0 || ft_atoi(color_splitted[i]) > 255)
			return (free_tab(color_splitted), 0);
		i++;
	}
	return (free_tab(color_splitted), 1);
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
