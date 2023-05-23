/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:44 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 14:13:10 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_and_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
	free_textures(&data->parsing);
	free_tab(data->parsing.map);
	exit(0);
}

// Exit cross
int	hook(void *mlx)
{
	free_and_exit(mlx);
	exit (0);
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESQ)
		free_and_exit(data);
	// else if (keycode == UP || keycode == DOWN)
	// 	hook_up_down(data, keycode);
	// else if (keycode == LEFT || keycode == RIGHT)
	// 	hook_left_right(data, keycode);
	// else if (keycode == A)
	// 	hook_a(data);
	// else if (keycode == D)
	// 	hook_d(data);
	print_img(data);
	return (1);
}