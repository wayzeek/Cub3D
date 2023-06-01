/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:18:03 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 20:27:40 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_parsing(t_data *data)
{
	data->parsing.color_ceiling = -1;
	data->parsing.color_floor = -1;
	data->parsing.path_texture_north = NULL;
	data->parsing.path_texture_south = NULL;
	data->parsing.path_texture_west = NULL;
	data->parsing.path_texture_east = NULL;
	data->parsing.map = NULL;
}

int	parsing_is_filled(t_data *data)
{
	if (data->parsing.color_floor != -1 && \
	data->parsing.color_ceiling != -1 && \
	data->parsing.path_texture_north != NULL \
	&& data->parsing.path_texture_south != NULL \
	&& data->parsing.path_texture_east != NULL \
	&& data->parsing.path_texture_west != NULL)
		return (1);
	return (0);
}

int	get_index_first_char(char *str)
{
	int	i;

	i = 0;
	while (ft_contains(" ", str[i]))
		i++;
	return (i);
}

int	check_extension(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i])
		i++;
	if (i < 5)
		return (0);
	if (map_name[i - 1] != 'b' || map_name[i - 2] != 'u' \
	|| map_name[i - 3] != 'c' || map_name[i - 4] != '.')
		return (0);
	return (1);
}
