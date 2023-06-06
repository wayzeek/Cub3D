/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:50:56 by vcart             #+#    #+#             */
/*   Updated: 2023/05/30 13:36:38 by vcart            ###   ########.fr       */
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

/*
 * draw for each ray the wall (a centered segment)
 * calculate the height of the wall based on the lenght of the ray
 */
void	draw_vert_ray(t_data *data, t_ray *ray)
{
	int		id;
	double	length;

	id = ray->id;
	ray->length = (1.0 / ray->length * WIN_HEIGHT) * 300; //arbitrary
	if (ray->length > WIN_HEIGHT || ray->length < 0)
		ray->length = WIN_HEIGHT;
//    if (id >= 0 && id <= 20)
//        printf("ray %d, lenght %d\n", id, ray->sq_length);
	if (ray->side_hit == 0)
		draw_seg(data, (t_vector){id, WIN_HEIGHT / 2 - ray->length / 2}, \
	(t_vector){id, WIN_HEIGHT / 2 + ray->length / 2}, N_WALL);
	else if (ray->side_hit == 1)
		draw_seg(data, (t_vector){id, WIN_HEIGHT / 2 - ray->length / 2}, \
	(t_vector){id, WIN_HEIGHT / 2 + ray->length / 2}, S_WALL);
	else if (ray->side_hit == 2)
		draw_seg(data, (t_vector){id, WIN_HEIGHT / 2 - ray->length / 2}, \
	(t_vector){id, WIN_HEIGHT / 2 + ray->length / 2}, E_WALL);
	else if (ray->side_hit == 3)
		draw_seg(data, (t_vector){id, WIN_HEIGHT / 2 - ray->length / 2}, \
	(t_vector){id, WIN_HEIGHT / 2 + ray->length / 2}, W_WALL);
}
