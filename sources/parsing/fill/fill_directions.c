/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:02:49 by vcart             #+#    #+#             */
/*   Updated: 2023/06/07 19:25:23 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_xpm(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 5)
		return (0);
	if (file[i - 1] != 'm' || file[i - 2] != 'p' \
	|| file[i - 3] != 'x' || file[i - 4] != '.')
		return (0);
	return (1);
}

char	*get_path(char *line)
{
	char	**line_split;
	char	*path;
	int		fd;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (printf("Error\n"), NULL);
	if (len_tab(line_split) != 2)
		return (printf("Error\nTextures not complete!\n"), \
		free_tab(line_split), NULL);
	if (!check_xpm(line_split[1]))
		return (printf("Error\nExpecting .xpm file!\n"), \
		free_tab(line_split), NULL);
	path = ft_strdup(line_split[1]);
	if (!path)
		return (printf("Error\n"), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nTextures files not found in %s\n", path), \
		free_tab(line_split), free(path), NULL);
	close(fd);
	return (free_tab(line_split), path);
}
