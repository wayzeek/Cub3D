/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:34:37 by vcart             #+#    #+#             */
/*   Updated: 2023/05/30 13:35:56 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * line drawing algorithm
 * first calculates the distance between the two vectors
 * then determines the number of steps required to draw a line between them
 *
 * then calculates the increment values for the x and y
 * for each step based on the distance and number of steps.
 */

void	draw_segment(t_data *data, t_vector vec1, t_vector vec2, int color)
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
		if (vec1.x >= 0 && vec1.x <= data->minimap_length && vec1.y >= 0 && vec1.y <= data->minimap_height)
			mlx_pixel_put_img(&data->img_minimap, vec1.x, vec1.y, color);
		vec1.x += increment.x;
		vec1.y += increment.y;
	}
}

void	draw_seg(t_data *data, t_vector vec1, t_vector vec2, int color)
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

void	floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			mlx_pixel_put_img(&data->img, x, y, data->parsing.color_ceiling);
			mlx_pixel_put_img(&data->img, x, y + WIN_HEIGHT / 2, data->parsing.color_floor);
			y++;
		}
		x++;
	}
}