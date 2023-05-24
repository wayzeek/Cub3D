/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:44 by vcart             #+#    #+#             */
/*   Updated: 2023/05/24 13:24:22 by vcart            ###   ########.fr       */
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

static int	check_possible_move(t_data *data, int keycode)
{
	if (keycode == W && (data->parsing.map[(int)(data->player.pos.y \
	+ data->player.dir.y * SPEED) / data->tile_size] \
	[(int)(data->player.pos.x + data->player.dir.x \
	* SPEED) / data->tile_size] != '1'))
		return (1);
	else if (keycode == S && (data->parsing.map[(int)(data->player.pos.y \
	+ data->tile_size / 4 - data->player.dir.y * SPEED) / data->tile_size] \
	[(int)(data->player.pos.x - data->player.dir.x * SPEED) \
	/ data->tile_size] != '1'))
		return (1);
	else if (keycode == A && (data->parsing.map[(int)(data->player.pos.y - \
	data->player.dir.x * SPEED) / data->tile_size][(int)(data->player.pos.x \
	+ data->player.dir.y * SPEED) / data->tile_size] != '1'))
		return (1);
	else if (keycode == D && (data->parsing.map[(int)(data->player.pos.y + \
	data->player.dir.x * SPEED) / data->tile_size][(int)(data->player.pos.x + \
	data->tile_size / 4 - data->player.dir.y * SPEED) / data->tile_size] != \
	'1'))
		return (1);
	return (0);
}

static void	handle_move(t_data *data, int keycode)
{
	if (!check_possible_move(data, keycode))
		return ;
	if (keycode == W)
	{
		data->player.pos.x += data->player.dir.x * SPEED;
		data->player.pos.y += data->player.dir.y * SPEED;
	}
	else if (keycode == S)
	{
		data->player.pos.x -= data->player.dir.x * SPEED;
		data->player.pos.y -= data->player.dir.y * SPEED;
	}
	else if (keycode == A)
	{
		data->player.pos.x += data->player.dir.y * SPEED;
		data->player.pos.y -= data->player.dir.x * SPEED;
	}
	else if (keycode == D)
	{
		data->player.pos.x -= data->player.dir.y * SPEED;
		data->player.pos.y += data->player.dir.x * SPEED;
	}
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESQ)
		free_and_exit(data);
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		handle_move(data, keycode);
	else if (keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == LEFT)
			data->angle_master -= 0.1;
		else
			data->angle_master += 0.1;
		data->player.dir.x = cos(data->angle_master);
		data->player.dir.y = sin(data->angle_master);
	}
	print_img(data);
	return (1);
}
