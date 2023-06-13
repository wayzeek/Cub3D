/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:47:55 by vcart             #+#    #+#             */
/*   Updated: 2023/06/13 21:03:53 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	len_no_spaces(char *line)
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

static int	count_line_map(char *line, int *mode)
{
	char	*new_line;

	new_line = remove_spaces(line);
	if (new_line[0] == '1' || new_line[0] == '0')
	{
		*mode = 1;
		return (free(new_line), free(line), 1);
	}
	free(line);
	free(new_line);
	return (0);
}

int	get_map_size(char *map_name)
{
	int		fd;
	int		map_size;
	char	*line;
	int		mode;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (printf("Error can't open map file\n"), -1);
	line = get_next_line(fd);
	mode = 0;
	map_size = 0;
	while (line)
	{
		if (is_empty_line(line) && mode == 1)
			break ;
		map_size += count_line_map(line, &mode);
		line = get_next_line(fd);
	}
	return (free(line), close(fd), map_size - 1);
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
		if (!ft_contains(" ", line[i]))
		{
			result[j] = line[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*remove_nl(char *line)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (!ft_contains("\n", line[i]))
		{
			result[j] = line[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
