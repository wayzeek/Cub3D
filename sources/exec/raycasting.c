/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:49:20 by jprofit           #+#    #+#             */
/*   Updated: 2023/05/24 11:58:05 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * initalize values and sets some of them to ensure working algorithm in
 * all 4 directions
 * ray->dir is normalized (just by not adding the current x and y)
 */
static void	init_dda(t_data *data, t_ray *ray, int i)
{
	ray->id = i;
	ray->start = (t_vector){data->player.pos.x, data->player.pos.y};
	ray->map = ray->start;
	ray->dir = (t_vector){cos(ray->angle), sin(ray->angle)};
	ray->deltadist = (t_vector){fabs(1.0 / ray->dir.x), fabs(1.0 / ray->dir.y)};

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (ray->start.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - ray->start.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (ray->start.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - ray->start.y) * ray->deltadist.y;
	}
}

/*
 * finds the quickest way to get from the next x
 * might be the x or y axis
 */
static void	dda(t_data *data, t_ray *ray)
{
	t_point	cell;
	int		hit;

	hit = FALSE;
	while (!hit && ray->map.x <= WIN_WIDTH && ray->map.y <= WIN_HEIGHT)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
		}
		cell = (t_point) {ray->map.x / data->tile_size, ray->map.y / data->tile_size};
		if (data->parsing.map[cell.y][cell.x] == '1')
			hit = TRUE;
		ray->sq_lenght = get_seg_length_squared(ray->start, ray->map); // * cos(ray->angle);
	}
	ray->hit = (t_point){ray->map.x, ray->map.y};
}

void static show_angle(t_data *data, t_ray ray)
{
	if ((ray.id >= 10 && ray.id <= 12) || (ray.id >= WIN_WIDTH - 12 && ray.id <= WIN_WIDTH - 10))
		draw_segment(data, (t_vector){data->player.pos.x, data->player.pos.y}, (t_vector){ray.map.x, ray.map.y}, 0x721d80);
	if (ray.id >= WIN_WIDTH / 2 - 1 && ray.id <= WIN_WIDTH / 2 + 1)
		draw_segment(data, (t_vector){data->player.pos.x, data->player.pos.y}, (t_vector){ray.map.x, ray.map.y}, 0x3b0f42);
}

void	raycasting(t_data *data)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_angle(data, i);
		init_dda(data, &data->ray_tab[i], i);
		dda(data, &data->ray_tab[i]);
		draw_vert_ray(data, &data->ray_tab[i]);
//		draw_segment(data, (t_vector){data->player.pos.x, data->player.pos.y}, (t_vector){data->ray_tab[i].map.x, data->ray_tab[i].map.y}, 0xc4b4b3);
//		show_angle(data, data->ray_tab[i]);
	}
}