/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:27:41 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:27:41 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ray_init(t_data *data)
{
	data->ray.cam_x = (2 * (double)data->x / (double)data->screen_width) - 1;
	data->ray.ray_pos_x = data->cam.pos_x;
	data->ray.ray_pos_y = data->cam.pos_y;
	data->ray.ray_dir_x = data->cam.dir_x + data->cam.plane_x * data->ray.cam_x;
	data->ray.ray_dir_y = data->cam.dir_y + data->cam.plane_y * data->ray.cam_x;
	data->ray.map_x = (int)data->ray.ray_pos_x;
	data->ray.map_y = (int)data->ray.ray_pos_y;
	data->ray.delta_dist_x = sqrt(1 + (data->ray.ray_dir_y
				* data->ray.ray_dir_y)
			/ (data->ray.ray_dir_x * data->ray.ray_dir_x));
	data->ray.delta_dist_y = sqrt(1 + (data->ray.ray_dir_x
				* data->ray.ray_dir_x)
			/ (data->ray.ray_dir_y * data->ray.ray_dir_y));
	data->ray.hit = 0;
}

void	ray_find_first_inter(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->ray.ray_pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1 - data->ray.ray_pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->ray.ray_pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1 - data->ray.ray_pos_y)
			* data->ray.delta_dist_y;
	}
}

void	ray_dda(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[(int)data->ray.map_y][(int)data->ray.map_x] == '1')
		{
			data->ray.hit = 1;
		}
	}
	perpendicular_wall_dist(data);
}

//distance perpandicular to camera plane
void	perpendicular_wall_dist(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->ray.wall_dist = fabs((data->ray.map_x - data->cam.pos_x
					+ (1 - data->ray.step_x) / 2) / data->ray.ray_dir_x);
	}
	else
	{
		data->ray.wall_dist = fabs((data->ray.map_y - data->cam.pos_y
					+ (1 - data->ray.step_y) / 2) / data->ray.ray_dir_y);
	}
}
