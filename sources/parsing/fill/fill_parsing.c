/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:17:44 by vcart             #+#    #+#             */
/*   Updated: 2023/06/08 13:50:26 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static t_img	ft_new_sprite(void *mlx, char *path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	if (img.img == NULL)
		return (img);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

static int	check_texture(t_img texture)
{
	if (texture.img == NULL || texture.addr == NULL)
		return (printf("Error\nTexture corrupted !\n"), 1);
	return (0);
}

int	fill_floor_ceiling(t_data *data, char *line, int mode)
{
	if (check_error_color(line))
		return (-1);
	if (mode == 'F')
	{
		data->parsing.color_floor = get_color(line);
		if (data->parsing.color_floor == -1)
			return (-1);
	}
	else
	{
		data->parsing.color_ceiling = get_color(line);
		if (data->parsing.color_ceiling == -1)
			return (-1);
	}
	return (0);
}

int	fill_directions(t_data *data, char *line, int mode)
{
	char	*path;

	path = NULL;
	line[ft_strlen(line) - 1] = '\0';
	if (mode == 'N')
	{
		path = get_path(line);
		if (path == NULL)
			return (free(path), -1);
		data->parsing.texture_north = ft_new_sprite(data->mlx_ptr, path);
		if (check_texture(data->parsing.texture_north))
			return (free(path), -1);
	}
	else if (mode == 'S')
	{
		path = get_path(line);
		if (path == NULL)
			return (free(path), -1);
		data->parsing.texture_south = ft_new_sprite(data->mlx_ptr, path);
		if (check_texture(data->parsing.texture_south))
			return (free(path), -1);
	}
	else if (mode == 'W')
	{
		path = get_path(line);
		if (path == NULL)
			return (free(path), -1);
		data->parsing.texture_west = ft_new_sprite(data->mlx_ptr, path);
		if (check_texture(data->parsing.texture_west))
			return (free(path), -1);
	}
	else if (mode == 'E')
	{
		path = get_path(line);
		if (path == NULL)
			return (free(path), -1);
		data->parsing.texture_east = ft_new_sprite(data->mlx_ptr, path);
		if (check_texture(data->parsing.texture_east))
			return (free(path), -1);
	}
	free(path);
	return (0);
}

static int	fill_each_line(t_data *data, char *line, int i)
{
	if (is_empty_line(line))
		return (0);
	data->parsing.map[i] = remove_nl(line);
	if (!data->parsing.map[i])
		return (printf("Error\n"), free(line), -1);
	if (data->parsing.map[i][0] == '\0')
	{
		free(data->parsing.map[i]);
		return (0);
	}
	if (i != 0)
		free(line);
	return (1);
}

int	fill_map(t_data *data, char *line, int map_size, int map_fd)
{
	int	i;
	int	ret;

	data->parsing.map = malloc(sizeof(char *) * (map_size + 2));
	if (!data->parsing.map)
		return (printf("Error\n"), -1);
	i = 0;
	while (line)
	{
		ret = fill_each_line(data, line, i);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (-1);
		line = get_next_line(map_fd);
		i++;
	}
	data->parsing.map[i] = NULL;
	free(line);
	if (check_map_error(data->parsing.map) == -1)
		return (-1);
	return (0);
}
