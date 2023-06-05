/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:50:48 by vcart             #+#    #+#             */
/*   Updated: 2023/06/05 15:49:44 by vcart            ###   ########.fr       */
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
	if (data->parsing.texture_north.img)
		mlx_destroy_image(&data->parsing.texture_north, data->parsing.texture_north.img);
	if (data->parsing.texture_south.img)
		mlx_destroy_image(&data->parsing.texture_south, data->parsing.texture_south.img);
	if (data->parsing.texture_west.img)
		mlx_destroy_image(&data->parsing.texture_west, data->parsing.texture_west.img);
	if (data->parsing.texture_east.img)
		mlx_destroy_image(&data->parsing.texture_east, data->parsing.texture_east.img);
}
