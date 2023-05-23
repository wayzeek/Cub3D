/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:02:25 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 11:35:22 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_textures(t_parsing *parsing)
{
	free(parsing->path_texture_east);
	free(parsing->path_texture_north);
	free(parsing->path_texture_south);
	free(parsing->path_texture_west);
}

void	free_parsing(t_parsing *parsing)
{
	free_textures(parsing);
	free_tab(parsing->map);
	free(parsing);
}

char	**complete_map(char	**map)
{
	int		i;
	int		biggest_len;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (len_tab(map) + 1));
	i = 0;
	biggest_len = get_len_longest_line(map);
	while (map[i])
	{
		new_map[i] = complete_line(map[i], biggest_len);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	check_each_line(char	*line, int i, int size, int position)
{
	char	*new_line;

	new_line = remove_spaces(line);
	if (!new_line)
		return (free(line), -1);
	if ((i == 0 || i == size) && check_border(new_line) == -1)
		return (free(line), -1);
	position += check_line_map(new_line);
	if (position < 0)
		return (free(line), -1);
	else if (position > 2)
		return (free(line), free(new_line), \
		printf("Error\nMultiple spawn points!\n"), -1);
	free(line);
	free(new_line);
	return (0);
}
