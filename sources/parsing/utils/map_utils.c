/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:42:58 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 15:35:10 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	get_len_longest_line(char	**map)
{
	int		i;
	size_t	max;

	max = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return ((int)(max));
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

char	**complete_map(char **map)
{
	int		i;
	int		size;
	char	**result;

	size = get_len_longest_line(map);
	result = malloc(sizeof(char *) * (len_tab(map) + 2));
	i = 0;
	while (map[i])
	{
		result[i] = complete_line(map[i], size);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	check_border(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (printf("Error\nMap not closed by walls!\n"), -1);
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
