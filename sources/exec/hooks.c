/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:02:44 by vcart             #+#    #+#             */
/*   Updated: 2023/06/13 14:56:01 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_and_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_image(data->mlx_ptr, data->img_minimap.img);
	mlx_destroy_window(data->mlx_ptr, data->win);
	free_all(data);
	exit(0);
}

// Exit cross
int	hook(void *mlx)
{
	free_and_exit(mlx);
	exit (0);
}

static t_point	simulate_next_pos(t_data *data, int keycode)
{
	t_point	next_pos;

	next_pos.x = data->player.pos.x;
	next_pos.y = data->player.pos.y;
	if (keycode == W)
	{
		next_pos.x = data->player.pos.x + data->player.dir.x * SPEED;
		next_pos.y = data->player.pos.y + data->player.dir.y * SPEED;
	}
	else if (keycode == S)
	{
		next_pos.x = data->player.pos.x - data->player.dir.x * SPEED;
		next_pos.y = data->player.pos.y - data->player.dir.y * SPEED;
	}
	else if (keycode == A)
	{
		next_pos.x = data->player.pos.x + data->player.dir.y * SPEED;
		next_pos.y = data->player.pos.y - data->player.dir.x * SPEED;
	}
	else if (keycode == D)
	{
		next_pos.x = data->player.pos.x - data->player.dir.y * SPEED;
		next_pos.y = data->player.pos.y + data->player.dir.x * SPEED;
	}
	return (next_pos);
}

static int	check_possible_move(t_data *data, int keycode)
{
	t_point	next_pos;

	next_pos = simulate_next_pos(data, keycode);
	if (!data->parsing.map[next_pos.y / data->tile_size] || !data->parsing.map \
	[next_pos.y / data->tile_size][next_pos.x / data->tile_size])
		return (0);
	if (data->parsing.map[next_pos.y / data->tile_size] \
	[next_pos.x / data->tile_size] == '1')
		return (0);
	if (data->parsing.map[next_pos.y / data->tile_size] \
	[next_pos.x / data->tile_size] == ' ')
		return (0);
	return (1);
}

static void	handle_move(t_data *data, int keycode)
{
	(void)check_possible_move(data, keycode);
	if (!check_possible_move(data, keycode))
		return ;
	if (keycode == W)
	{
		data->player.pos.x += (int)(data->player.dir.x * SPEED);
		data->player.pos.y += (int)(data->player.dir.y * SPEED);
	}
	else if (keycode == S)
	{
		data->player.pos.x -= (int)(data->player.dir.x * SPEED);
		data->player.pos.y -= (int)(data->player.dir.y * SPEED);
	}
	else if (keycode == A)
	{
		data->player.pos.x += (int)(data->player.dir.y * SPEED);
		data->player.pos.y -= (int)(data->player.dir.x * SPEED);
	}
	else if (keycode == D)
	{
		data->player.pos.x -= (int)(data->player.dir.y * SPEED);
		data->player.pos.y += (int)(data->player.dir.x * SPEED);
	}
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESQ)
		free_and_exit(data);
	else if (keycode == W || keycode == S || keycode == A || keycode == D)
		handle_move(data, keycode);
	else if (keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == LEFT)
			data->angle_master -= 0.05;
		else
			data->angle_master += 0.05;
		data->player.dir.x = cos(data->angle_master);
		data->player.dir.y = sin(data->angle_master);
	}
	print_img(data);
	return (1);
}
