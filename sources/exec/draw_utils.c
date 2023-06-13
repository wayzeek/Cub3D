/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:34:37 by vcart             #+#    #+#             */
/*   Updated: 2023/06/13 15:12:04 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		if (vec1.x >= 0 && vec1.x <= data->minimap_length \
			&& vec1.y >= 0 && vec1.y <= data->minimap_height)
			mlx_pixel_put_img(&data->img_minimap, vec1.x, vec1.y, color);
		vec1.x += increment.x;
		vec1.y += increment.y;
	}
}

void	draw_seg(t_data *data, t_ray *ray)
{
	ray->lineheight = (int)(WIN_HEIGHT / ray->length);
	ray->drawstart = -ray->lineheight / 2 + WIN_HEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + WIN_HEIGHT / 2;
	if (ray->drawend >= WIN_HEIGHT)
		ray->drawend = WIN_HEIGHT - 1;
	get_ray_texture(data, ray);
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->size.x);
	if (ray->side_hit <= 1 && ray->dir.x > 0)
		ray->tex_x = ray->texture->size.x - ray->tex_x - 1;
	else if (ray->side_hit >= 2 && ray->dir.y < 0)
		ray->tex_x = ray->texture->size.x - ray->tex_x - 1;
	ray->tex_step = 1.0 * ray->texture->size.y / ray->lineheight;
	ray->tex_pos = (ray->drawstart - WIN_HEIGHT / 2 + \
	ray->lineheight / 2) * ray->tex_step;
	draw_stripe(data, ray);
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
			mlx_pixel_put_img(&data->img, x, y + WIN_HEIGHT / 2, \
			data->parsing.color_floor);
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
	dst = data->addr + (y % data->size.y * data->line_length \
		+ x % data->size.x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}
