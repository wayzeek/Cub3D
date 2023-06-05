/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:02:49 by vcart             #+#    #+#             */
/*   Updated: 2023/06/05 14:10:48 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*get_path(char *line)
{
	char	**line_split;
	char	*path;
	int		fd;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (printf("Error\n"), NULL);
	path = ft_strdup(line_split[1]);
	if (!path)
		return (printf("Error\n"), NULL);
	path[ft_strlen(path) - 1] = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nTextures files not found in %s\n", path), \
		free_tab(line_split), free(path), NULL);
	close(fd);
	return (free_tab(line_split), path);
}
