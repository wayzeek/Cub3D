/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:30:46 by vcart             #+#    #+#             */
/*   Updated: 2023/05/30 15:02:32 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Defines

# define SUCCESS 0
# define ERROR 1
# define FALSE 0
# define TRUE 1
# define EMPTY 0
# define WALL 1
# define WIN_WIDTH 1500
# define WIN_HEIGHT 1000
# define PI 3.14159265358979323846
# define MAP_SIZE (WIN_WIDTH / 3)
# define FOV (PI / 4)
# define SPEED 5
# define CEILLING 0xB0C4DE

// Headers

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

// Local headers

# include "../sources/libft/libft.h"
# include "../sources/minilibx-linux/mlx.h"

// Keycodes

typedef enum e_keycode
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	O = 111,
	P = 112,
	R = 114,
	G = 103,
	B = 98,
	ESQ = 65307,
	TAB = 48,
	SPACE = 49,
	PLUS = 65451,
	MINUS = 65454,
	LEFT = 65361,
	RIGHT = 65363,
	DOWN = 65364,
	UP = 65362,
}	t_keycode;

// Parsing structure

typedef struct s_parsing
{
	char	*path_texture_north;
	char	*path_texture_south;
	char	*path_texture_west;
	char	*path_texture_east;

	int		color_floor;
	int		color_ceiling;

	int		map_size_width;
	char	**map;
}	t_parsing;

// Vector structure

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

// Point structure

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// Image structure

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// Ray structure

typedef struct s_ray
{
	int			id;
	t_vector	start;
	t_vector	dir;
	t_vector	map;
	t_vector	deltadist;
	t_vector	step;
	t_vector	sidedist;
	t_point		hit;
	double		angle;
	int			sq_lenght;
}	t_ray;

// Player structure
typedef struct s_player
{
	t_point		pos;
	t_vector	dir;
	char		dir_char;
}	t_player;

// Data structure

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_img		img_minimap;

	int			minimap_length;
	int			minimap_height;

	t_parsing	parsing;
	int			tile_size;
	t_player	player;
	double		angle_master;
	t_ray		ray_tab[WIN_WIDTH];
	int			max_ray_lenght;
}	t_data;

// main.c

int			main(int argc, char **argv);

// parsing.c

int			get_parsing(t_data	*data, char	*map_name);

// fill_parsing.c

int			create_trgb(int t, int r, int g, int b);
int			get_map(t_parsing *parsing, int map_fd, int map_size);
int			get_colors(t_parsing *parsing, int map_fd);
int			get_textures(t_parsing *parsing, int map_fd);
char		*go_to_beginning_text(int map_fd);

// parsing_utils.c

int			check_mode(char **line_splitted);
int			exec_mode(t_parsing *parsing, int map_fd, int mode);
int			fill_textures(char *line, t_parsing *parsing);
int			fill_colors(char *line, t_parsing *parsing);
char		**fill_map(char	*line, int map_size, int map_fd);


// error_utils.c

int			len_tab(char **tab);
int			valid_directions_id(char *str);
int			valid_colors_id(char *str);
int			valid_rgb(char	*str);
char		*complete_line(char	*str, int size);

// error_map.c

int			check_map(int map_fd, int size);
int			check_line_map(char	*line);
int			check_border(char *line);
int			line_is_closed(char *line);
int			map_is_closed(char	**map);

// error_colors.c

int			check_colors(int map_fd);
int			check_line_colors(char	*line);

// error_map_utils.c

int			is_ok_for_map(char *line);
char		*remove_spaces(char *line);
int			get_map_size(int map_fd);
int			get_len_longest_line(char	**map);

// error_directions.c

int			check_directions(int map_fd);
int			check_line_directions(char	*line);

// free.c

void		free_tab(char **tab);
char		**complete_map(char	**map);
void		free_textures(t_parsing *parsing);
int			check_each_line(char	*line, int i, int size, int position);
int			check_player(t_data *data);

// init.c

int			init_all(t_data *data);
void		init_angle(t_data *data, int i);

// print.c

void		print_img(t_data *data);

// draw.c

void		mlx_pixel_put_img(t_img *img, int x, int y, int color);
void		put_tile(t_data *data, int x, int y, int color);
void		print_square(t_data *data, int x, int y, int size);
void		draw_vert_ray(t_data *data, t_ray *ray);

// draw_utils.c

void		draw_segment(t_data *data, t_vector vec1, t_vector vec2, int color);
void		draw_seg(t_data *data, t_vector vec1, t_vector vec2, int color);
void		floor_ceiling(t_data *data);

// hooks.c

int			key_hook(int keycode, t_data *data);
int			hook(void *mlx);

// raycasting.c

void		raycasting(t_data *data);

// utils.c

int			get_seg_length_squared(t_vector vec1, t_vector vec2);

#endif