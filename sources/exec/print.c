/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:15 by vcart             #+#    #+#             */
/*   Updated: 2023/05/26 11:42:13 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	create_map_img(t_data *data, t_parsing *parsing)
{
	int	x;
	int	y;

	y = -1;
	while (parsing->map[++y])
	{
		x = 0;
		while (parsing->map[y][x])
		{
			if (parsing->map[y][x] == '1')
				put_tile(data, x, y, 0xC07F00);
			else if (ft_contains(" /t/n/r/v/f", parsing->map[y][x]))
				put_tile(data, x, y, 0x4C3D3D);
			else
				put_tile(data, x, y, 0xFFF7D4);
			print_square(data, data->player.pos.x, \
			data->player.pos.y, data->tile_size / 4);
			x++;
		}
	}
}

void	print_img(t_data *data)
{
	create_map_img(data, &data->parsing);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img_minimap.img, 0, 0);
}
