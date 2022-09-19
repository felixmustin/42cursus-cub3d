#include "main.h"

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == K_AR_D) {
		data->cam.front = true;
    }
	else if (keycode == K_AR_U)
		data->cam.back = true;
	else if (keycode == K_AR_L)
		data->cam.left = true;
	else if (keycode == K_AR_R)
		data->cam.right = true;
    else if (keycode == K_G) {
		data->cam.rotate = true;
        data->cam.rot_speed = -0.1;
    }
    else if (keycode == K_H) {
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
	if (keycode == K_AR_D) {
		data->cam.front = false;
    }
	else if (keycode == K_AR_U)
		data->cam.back = false;
	else if (keycode == K_AR_L)
		data->cam.left = false;
	else if (keycode == K_AR_R)
		data->cam.right = false;
    else if (keycode == K_G) {
		data->cam.rotate = false;
    }
    else if (keycode == K_H) {
		data->cam.rotate = false;
    }
	return (1);
}