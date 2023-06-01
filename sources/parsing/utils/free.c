/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:50:48 by vcart             #+#    #+#             */
/*   Updated: 2023/06/01 11:59:52 by vcart            ###   ########.fr       */
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

void	free_all(t_data *data)
{
	if (data->parsing.map)
		free_tab(data->parsing.map);
	if (data->parsing.path_texture_north)
		free(data->parsing.path_texture_north);
	if (data->parsing.path_texture_south)
		free(data->parsing.path_texture_south);
	if (data->parsing.path_texture_west)
		free(data->parsing.path_texture_west);
	if (data->parsing.path_texture_east)
		free(data->parsing.path_texture_east);
}
