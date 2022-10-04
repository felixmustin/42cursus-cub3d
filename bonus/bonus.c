#include "main.h"

void	init_bonus(t_data *data)
{
	data->cam.display = true;
	data->sprr = malloc(sizeof(char *) * (2));
	data->sprr[0] = "textures/purplestone.xpm";
	data->sprr[1] = "textures/wood.xpm";
	data->spr_tab = malloc(sizeof(char *) * (2));
	data->spr = malloc(sizeof(void *) * (2));
}

void	replace_mouse(t_data *data)
{
	mlx_mouse_move(data->mlx.mlx_win, data->screen_width / 2,
		data->screen_heigth / 2);
	mlx_mouse_hide();
}

void	display_menu(t_data *data)
{
	if (data->menu == false)
	{
		data->menu = true;
		data->cam.front = false;
		data->cam.back = false;
		data->cam.left = false;
		data->cam.right = false;
		data->cam.rotate = false;
		mlx_mouse_show();
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.mlx_win,
			data->screen_width / 2 - 20, data->screen_heigth / 2,
			0xFFFFFF, "Pause");
		data->cam.display = false;
	}
	else if (data->menu == true)
	{
		data->menu = false;
		replace_mouse(data);
		data->cam.display = true;
	}
}
