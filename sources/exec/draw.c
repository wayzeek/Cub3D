/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:50:56 by vcart             #+#    #+#             */
/*   Updated: 2023/05/24 12:51:24 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	mlx_pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	put_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * data->tile_size;
	while (i <= x * data->tile_size + data->tile_size)
	{
		j = y * data->tile_size;
		while (j < y * data->tile_size + data->tile_size)
		{
			mlx_pixel_put_img(&data->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	print_square(t_data *data, int x, int y, int size)
{
	int	i;
	int	j;

	i = x;
	while (i <= x + size)
	{
		j = y;
		while (j <= y + size)
		{
			mlx_pixel_put_img(&data->img, i, j, 0x2133bf);
			j++;
		}
		i++;
	}
}

/*
 * line drawing algorithm
 * first calculates the distance between the two vectors
 * then determines the number of steps required to draw a line between them
 *
 * then calculates the increment values for the x and y
 * for each step based on the distance and number of steps.
 */
void draw_segment(t_data *data, t_vector vec1, t_vector vec2, int color)
{
	t_point		delta;
	t_vector	increment;
	int			steps;
	int			i;

	delta.x = vec2.x - vec1.x;
	delta.y = vec2.y - vec1.y;

	if (abs(delta.x) > abs(delta.y))
		steps = abs(delta.x);
	else
		steps = abs(delta.y);
	increment.x = delta.x / (float)steps;
	increment.y = delta.y / (float)steps;

	i = -1;
	while (++i <= steps)
	{
		if (vec1.x >= 0 && vec1.x <= WIN_WIDTH && vec1.y >= 0 && vec1.y <= WIN_HEIGHT)
			mlx_pixel_put_img(&data->img, vec1.x, vec1.y, color);
		vec1.x += increment.x;
		vec1.y += increment.y;
	}
}

/*
 * draw for each ray the sky, the wall then the floor
 * calculate the height of the wall based on the lenght of the ray
 */
void	draw_vert_ray(t_data *data, t_ray *ray)
{
	int		id;
	double	length;

	id = ray->id;
	length = 1.0 / ray->sq_lenght * (WIN_WIDTH * WIN_WIDTH);
	draw_segment(data, (t_vector){id, 0}, (t_vector){id, WIN_HEIGHT / 2 - length / 2}, 0xb52424); //ceiling
	draw_segment(data, (t_vector){id, WIN_HEIGHT / 2 - length / 2}, (t_vector){id, WIN_HEIGHT / 2 + length / 2}, 0xeeff00); //wall
	draw_segment(data, (t_vector){id, WIN_HEIGHT / 2 + length / 2}, (t_vector){id, WIN_HEIGHT}, 0x24b54f); // floor
}
