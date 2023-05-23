/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:39:32 by vcart             #+#    #+#             */
/*   Updated: 2023/05/23 12:58:23 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_tile_size(t_parsing *parsing)
{
	if (WIN_HEIGHT >= WIN_WIDTH)
		return (WIN_WIDTH / get_len_longest_line(parsing->map));
	else
		return (WIN_HEIGHT / get_len_longest_line(parsing->map));
}

// Sets in radian the player's starting direction
static void	set_ray_master(t_data *data)
{
	if (data->player->dir_char == 'E')
		data->angle_master = 0;
	else if (data->player->dir_char == 'N')
		data->angle_master = -PI / 2;
	else if (data->player->dir_char == 'S')
		data->angle_master = PI / 2;
	else if (data->player->dir_char == 'W')
		data->angle_master = PI;
	data->player->dir.x = cos(data->angle_master);
	data->player->dir.y = sin(data->angle_master);
}

static int	create_all(t_data *data)
{
	int	i;

	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (ERROR);
	data->ray_tab = malloc(sizeof(t_ray) * (WIN_WIDTH + 1));
	if (!data->ray_tab)
		return (ERROR);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		data->ray_tab[i] = malloc(sizeof(t_ray));
		if (!data->ray_tab[i])
			return (ERROR);
	}
	return (SUCCESS);
}

static void	get_player_position(char **map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_contains("NSEW", map[y][x]))
			{
				data->player->pos.x = x * data->tile_size;
				data->player->pos.y = y * data->tile_size;
				data->player->dir_char = map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_all(t_data *data, t_parsing *parsing)
{
	if (create_all(data))
		return (ERROR);
	data->mlx_ptr = mlx_init();
	data->parsing = parsing;
	data->tile_size = get_tile_size(parsing);
	data->parsing->map_size_width = get_len_longest_line(parsing->map);
	data->max_ray_lenght = 10 * data->tile_size;
	get_player_position(parsing->map, data);
	set_ray_master(data);
	return (SUCCESS);
}
