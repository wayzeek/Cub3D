/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:02:49 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 12:00:17 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*get_path(char *line)
{
	char	**line_split;
	char	*path;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (printf("Error\n"), NULL);
	path = ft_strdup(line_split[1]);
	if (!path)
		return (printf("Error\n"), NULL);
	return (free_tab(line_split), path);
}

