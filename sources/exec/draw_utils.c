/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:34:37 by vcart             #+#    #+#             */
/*   Updated: 2023/06/08 11:28:44 by vcart            ###   ########.fr       */
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

/*static int	ft_calculate_height(t_ray *ray)
{
	if (ray->boolean)
		ray->length = \
			(ray->sidedist.x - ray->deltadist.x);
	else
		ray->length = \
			(ray->sidedist.y - ray->deltadist.y);
	return ((int)(WIN_HEIGHT / ray->length));
}*/

void	draw_seg(t_data *data, t_ray *ray)
{
	double 		wall_x;
	int 		y;

	// Getting start and end of the line to draw
	int lineheight = (int)(WIN_HEIGHT / ray->length * 3.5);
	int drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	int drawend = lineheight / 2 + WIN_HEIGHT / 2;
	if (drawend >= WIN_HEIGHT)
		drawend = WIN_HEIGHT - 1;

	//Getting texture based on side hit
	if (ray->side_hit == 0)
		ray->texture = &data->parsing.texture_north;
	else if (ray->side_hit == 1)
		ray->texture = &data->parsing.texture_east;
	else if (ray->side_hit == 2)
		ray->texture = &data->parsing.texture_south;
	else if (ray->side_hit == 3)
		ray->texture = &data->parsing.texture_west;

	// Calculate the X coordinate of the wall hit
	if (ray->boolean)
		wall_x = ray->start.y + ray->length * ray->dir.y;
	else
		wall_x = ray->start.x + ray->length * ray->dir.x;

	// X coordinate on the texture
	int tex_x = (int)(wall_x * (double)ray->texture->size.x);
	if (ray->side_hit <= 1 && ray->dir.x > 0)
		tex_x = ray->texture->size.x - tex_x - 1;
	else if (ray->side_hit >= 2 && ray->dir.y < 0)
		tex_x = ray->texture->size.x - tex_x - 1;

	// Calculate the step of the texture
	double step = 1.0 * ray->texture->size.y / lineheight;

	// Calculate the starting texture coordinate
	double tex_pos = (drawstart - WIN_HEIGHT / 2 + lineheight / 2) * step;
	
	// Draw the pixels of the stripe as a vertical line
	y = drawstart;
	while (y < drawend)
	{
		int tex_y = (int)tex_pos & (ray->texture->size.y - 1);
		tex_pos += step;
		int color = get_text_color(ray->texture, tex_x, tex_y);
		mlx_pixel_put_img(&data->img, ray->x, y, color);
		y++;
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

int	get_text_color(t_img *data, int x, int y)
{
	int		color;
	char	*dst;

	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	dst = data->addr + (y % data->size.y * data->line_length + x % data->size.x * \
		(data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}