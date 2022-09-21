#include "main.h"

int mouse_move(int x, int y, t_data *data)
{
    (void) y;
    data->cam.rot_speed = ((x * 0.15)  - ((data->screen_width / 2) * 0.15)) * 0.06;
    rotate_cam(&data->cam);
    if (x != data->screen_width / 2)
        mlx_mouse_move(data->mlx.mlx_win, data->screen_width/2, data->screen_heigth/2);
    return (1);
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == K_Z) {
		data->cam.front = true;
    }
	else if (keycode == K_S)
		data->cam.back = true;
	else if (keycode == K_Q)
		data->cam.left = true;
	else if (keycode == K_D)
		data->cam.right = true;
    else if (keycode == K_AR_L) {
		data->cam.rotate = true;
        data->cam.rot_speed = -0.1;
    }
    else if (keycode == K_AR_R) {
		data->cam.rotate = true;
        data->cam.rot_speed = 0.1;
    }
    else if (keycode == K_ESC) {
        data->leave = 1;
    }
	return (1);
}

int	ft_key_release(int keycode, t_data *data)
{
	if (keycode == K_Z) {
		data->cam.front = false;
    }
	else if (keycode == K_S)
		data->cam.back = false;
	else if (keycode == K_Q)
		data->cam.left = false;
	else if (keycode == K_D)
		data->cam.right = false;
    else if (keycode == K_AR_L) {
		data->cam.rotate = false;
    }
    else if (keycode == K_AR_R) {
		data->cam.rotate = false;
    }
	return (1);
}