/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:53:00 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:35:15 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	is_ok_for_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_contains("01NSEW ", line[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (ft_contains("NSEW ", line[i]))
			return (2);
		i++;
	}
	return (0);
}

int	len_no_spaces(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

char	*remove_spaces(char *line)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (len_no_spaces(line) + 1));
	while (line[i])
	{
		if (!ft_contains(" \t\n\r\v\f", line[i]))
		{
			result[j] = line[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	get_map_size(int map_fd)
{
	int		size;
	char	*line;

	size = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] != '\n')
			size++;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (size - 7);
}

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
