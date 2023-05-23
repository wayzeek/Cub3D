/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:53 by jprofit           #+#    #+#             */
/*   Updated: 2023/05/23 13:13:26 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_parsing(data->parsing);
	free(data->player);
	while (++i < WIN_WIDTH)
		free(data->ray_tab[i]);
	free(data->ray_tab);
	free(data);
}

int	main(int argc, char **argv)
{
	t_parsing	*parsing;
	t_data		data;
	(void)		argc;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (1);
	if (get_parsing(parsing, argv[1]) == -1)
		return (1);
	printf("Map is valid !\n\n");
	init_all(&data, parsing);
	data.win = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	print_img(&data, parsing);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.win, 17, 0, hook, &data);
	mlx_loop(data.mlx_ptr);
	free_parsing(parsing);
	return (0);
}
