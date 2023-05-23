/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:44 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 15:03:42 by vcart            ###   ########.fr       */
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
	printf("Player : %d %d\n", data->player.pos.x, data->player.pos.y);
	if (keycode == ESQ)
		free_and_exit(data);
	else if (keycode == UP)
	{
		data->player.pos.x += data->player.dir.x * SPEED;
		data->player.pos.y += data->player.dir.y * SPEED;
	}
	else if (keycode == DOWN)
	{
		data->player.pos.x -= data->player.dir.x * SPEED;
		data->player.pos.y -= data->player.dir.y * SPEED;
	}
	else if (keycode == LEFT)
	{
		printf("LEFT\n");
		data->player.pos.x -= 10;
	}
	else if (keycode == RIGHT)
	{
		printf("RIGHT\n");
		data->player.pos.x += 10;
	}
	else if (keycode == A)
	{
		data->angle_master -= 0.1;
		data->player.dir.x = cos(data->angle_master);
		data->player.dir.y = sin(data->angle_master);
	}
	else if (keycode == D)
	{
		data->angle_master += 0.1;
		data->player.dir.x = cos(data->angle_master);
		data->player.dir.y = sin(data->angle_master);
	}
	print_img(data);
	return (1);
}