/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:50:56 by vcart             #+#    #+#             */
/*   Updated: 2023/06/13 15:11:41 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mlx_pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (img == NULL || img->addr == NULL)
		return ;
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
			mlx_pixel_put_img(&data->img_minimap, i, j, color);
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
			mlx_pixel_put_img(&data->img_minimap, i, j, 0x2133bf);
			j++;
		}
		i++;
	}
}

void	draw_stripe(t_data *data, t_ray *ray)
{
	int	y;
	int	tex_y;
	int	color;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		tex_y = (int)ray->tex_pos & (ray->texture->size.y - 1);
		ray->tex_pos += ray->tex_step;
		color = get_text_color(ray->texture, ray->tex_x, tex_y);
		mlx_pixel_put_img(&data->img, ray->x, y, color);
		y++;
	}
}

void	get_ray_texture(t_data *data, t_ray *ray)
{
	if (ray->side_hit == 0)
		ray->texture = &data->parsing.texture_north;
	else if (ray->side_hit == 1)
		ray->texture = &data->parsing.texture_east;
	else if (ray->side_hit == 2)
		ray->texture = &data->parsing.texture_south;
	else if (ray->side_hit == 3)
		ray->texture = &data->parsing.texture_west;
	if (ray->boolean)
		ray->wall_x = ray->start.y + ray->length * ray->dir.y;
	else
		ray->wall_x = ray->start.x + ray->length * ray->dir.x;
}
