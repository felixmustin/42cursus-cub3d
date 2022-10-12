/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:26:23 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:26:24 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../gnl/get_next_line.h"
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

# define K_Z 13
# define K_Q 0
# define K_S 1
# define K_D 2
# define K_P 35
# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 125
# define K_AR_D 126
# define K_ESC 53
# define K_SHFT 257

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_ray
{
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_pos_x;
	double	ray_pos_y;
	double	map_x;
	double	map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_dist;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}	t_mlx;

typedef struct s_tex
{
	void	**tex;
	char	**tex_tab;
	char	**textures;

	int		w;
	int		h;

	double	wall_x;
	int		tex_x;
	int		tex_y;

	double	floor_x;
	double	floor_y;
	int		floor_tex_x;
	int		floor_tex_y;
	double	pix_pos_x;
	double	pix_pos_y;

}	t_tex;

typedef struct s_cam
{
	double	pos_x;
	double	pos_y;

	double	dir_x;
	double	dir_y;

	double	plane_x;
	double	plane_y;

	bool	front;
	bool	back;
	bool	right;
	bool	left;
	bool	rotate;
	bool	display;
	double	rot_speed;
	double	speed;
}	t_cam;

typedef struct s_data
{
	t_cam	cam;
	t_ray	ray;
	t_mlx	mlx;
	t_tex	tex;

	char	**map;
	int		map_width;
	int		map_heigth;

	void	**spr;
	char	**spr_tab;
	char	**sprr;

	int		floor_color;
	int		ceiling_color;

	int		screen_width;
	int		screen_heigth;

	int		x;
	int		y;

	int		sizeminimap;
	int		minimap_x;
	int		minimap_y;

	int		line_height;
	int		draw_start;
	int		draw_end;

	int		color_int;

	bool	menu;
	int		leave;
}	t_data;

//EVENT
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);

//RAYCAST
void	raycast_wall(t_data *data);
void	raycast_floor_ceiling(t_data *data);
void	color_floor_ceiling(t_data *data);
void	ray_init(t_data *data);
void	ray_find_first_inter(t_data *data);
void	ray_dda(t_data *data);
void	perpendicular_wall_dist(t_data *data);

//mlx
void	my_mlx_pixel_put(t_data *data, int xx, int yy, int color);
void	ft_create_image(t_data *data);
void	ft_create_texture(t_data *data);
void	ft_clear_window(t_data *data);

//move
void	move(t_data *data, t_cam *cam);
void	rotate_cam(t_cam *cam);

int		leave(t_data *data);
void	display_menu(t_data *data);

void	minimap(t_data *data);
void	init_cursor(t_data *data);
void	init_bonus(t_data *data);
void	replace_mouse(t_data *data);

//parsing

int		parsing(int ac, char **av, t_data *data);
int		ft_strlen_split(char **str);
char	*ft_strdup_modif(char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		parsing_recover(int ac, char **av, t_data *data);
int		texture_recover(char **file, t_data *data, int i);
int		color_recover(int i, char **file, t_data *data);
int		map_recover(t_data *data, char **file, int i);
int		malloc_texture(t_data *data);
char	**file_recover(char *str);
int		parse_texture(t_data *data);
int		parser(t_data *data);
int		parse_map(t_data *data);
int		get_color(char	**str);
void	get_size(char **map, int *width, int *height);
int		check_map(char **map);
char	**file_to_texture(char *file);
void	free_tab(char **tab);
void	free_texture(t_data *data);
char	**file_to_string(char *file);

#endif
