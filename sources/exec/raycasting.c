/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:49:20 by jprofit           #+#    #+#             */
/*   Updated: 2023/05/30 13:28:44 by vcart            ###   ########.fr       */
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
			ray->last_incr = 'x';
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->last_incr = 'y';
		}
		cell = (t_point){ray->map.x / data->tile_size, ray->map.y / data->tile_size};
		if (data->parsing.map[cell.y][cell.x] == '1')
			hit = TRUE;
		ray->sq_lenght = get_seg_length_squared(ray->start, ray->map); // * cos(ray->angle);
	}
	ray->hit = (t_point){ray->map.x, ray->map.y};
}

static void	show_angle(t_data *data, t_ray ray)
{
	if ((ray.id >= 10 && ray.id <= 12) || (ray.id >= WIN_WIDTH - 12 && ray.id <= WIN_WIDTH - 10))
		draw_segment(data, (t_vector){data->player.pos.x + data->tile_size / 8, data->player.pos.y + data->tile_size / 8}, (t_vector){ray.map.x, ray.map.y}, 0x721d80);
	if (ray.id >= WIN_WIDTH / 2 - 1 && ray.id <= WIN_WIDTH / 2 + 1)
		draw_segment(data, (t_vector){data->player.pos.x + data->tile_size / 8, data->player.pos.y + data->tile_size / 8}, (t_vector){ray.map.x, ray.map.y}, 0x3b0f42);
}

/*
 * used to set side_hit to the appropriate value (0=N, 1=E, 2=S, 3=W)
 * if the last increment is x, the side of the box that could have been hit are
 * E or W, and if the step is positive it can only be the E side
 */
void	side_hit(t_ray *ray)
{
	if (ray->last_incr == 'x')
	{
		if (ray->step.x == 1)
			ray->side_hit = 3;
		else
			ray->side_hit = 1;
	}
	else
	{
		if (ray->step.y == 1)
			ray->side_hit = 0;
		else
			ray->side_hit = 2;
	}
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
		side_hit(&data->ray_tab[i]);
		show_angle(data, data->ray_tab[i]);
		draw_vert_ray(data, &data->ray_tab[i]);
	}
}
