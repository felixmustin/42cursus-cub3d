#include "main.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_heigth)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	i = 0;
	while (i < 5)
	{
		free(data->tex.textures[i]);
		i++;
	}
	free(data->tex.tex);
	free(data->tex.tex_tab);
	free(data->tex.textures);
}

int	leave(t_data *data)
{
	ft_clear_window(data);
	ft_free(data);
	exit (1);
}

int	render(t_data *data)
{
	if (data->cam.display)
	{
		data->cam.display = false;
		data->x = 0;
		data->y = 0;
		move(data, &data->cam);
		while (data->x < data->screen_width)
		{
			raycast_wall(data);
			raycast_floor_ceiling(data);
			data->x++;
		}
		minimap(data);
		init_cursor(data);
		data->cam.display = true;
	}
	if (data->leave)
		leave(data);
	else if (!data->menu)
	{
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win,
			data->mlx.mlx_img, 0, 0);
	}
	return (1);
}

void	prepare(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx_ptr, data->screen_width,
			data->screen_heigth, "cub3d");
	ft_create_texture(data);
	ft_create_image(data);
	mlx_hook(data->mlx.mlx_win, ON_KEYDOWN, 1L << 0, ft_key_press, data);
	mlx_hook(data->mlx.mlx_win, ON_KEYUP, 1L << 1, ft_key_release, data);
	mlx_hook(data->mlx.mlx_win, ON_DESTROY, 0, leave, data);
	replace_mouse(data);
	mlx_hook(data->mlx.mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);
	mlx_loop_hook(data->mlx.mlx_ptr, render, data);
	mlx_loop(data->mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	parsing(argc, argv, &data);
	init_bonus(&data);
	prepare(&data);
}
