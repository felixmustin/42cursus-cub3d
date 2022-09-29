#include "main.h"

void	ft_key_press_2(int keycode, t_data *data)
{
	if (keycode == K_AR_L)
	{
		data->cam.rotate = true;
		data->cam.rot_speed = -0.1;
	}
	else if (keycode == K_AR_R)
	{
		data->cam.rotate = true;
		data->cam.rot_speed = 0.1;
	}	
	else if (keycode == K_SHFT)
        data->cam.speed += 0.05;
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == K_ESC)
        data->leave = 1;

	if (keycode == K_Z)
		data->cam.front = true;
	else if (keycode == K_S)
		data->cam.back = true;
	else if (keycode == K_Q)
		data->cam.left = true;
	else if (keycode == K_D)
		data->cam.right = true;
	ft_key_press_2(keycode, data);
	return (1);
}

int	ft_key_release(int keycode, t_data *data)
{
	if (keycode == K_Z)
		data->cam.front = false;
	else if (keycode == K_S)
		data->cam.back = false;
	else if (keycode == K_Q)
		data->cam.left = false;
	else if (keycode == K_D)
		data->cam.right = false;
	else if (keycode == K_AR_L)
		data->cam.rotate = false;
	else if (keycode == K_AR_R)
		data->cam.rotate = false;
	else if (keycode == K_SHFT)
		data->cam.speed -= 0.05;
	return (1);
}