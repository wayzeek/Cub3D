/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:53 by jprofit           #+#    #+#             */
/*   Updated: 2023/06/03 14:01:20 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		return (printf("Error\nPlease use : ./cub3D [map_path]\n"), 1);
	if (get_parsing(&data, argv[1]) == -1)
		return (free_all(&data), 1);
	if (!parsing_is_filled(&data) || data.parsing.map == NULL)
		return (printf("Error\n.cub file not completed properly\n"), free_all(&data), 1);
	printf("Map is valid !\n");
	init_all(&data);
	data.win = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, \
	&data.img.line_length, &data.img.endian);
	data.img_minimap.img = mlx_new_image(data.mlx_ptr, data.minimap_length, data.minimap_height);
	data.img_minimap.addr = mlx_get_data_addr(data.img_minimap.img, &data.img_minimap.bits_per_pixel, \
	&data.img_minimap.line_length, &data.img_minimap.endian);
	print_img(&data);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.win, 17, 0, hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
