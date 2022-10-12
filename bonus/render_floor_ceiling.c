/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:27:27 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:27:28 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ray_texel_pos(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
	{
		data->tex.floor_x = data->ray.map_x;
		data->tex.floor_y = data->ray.map_y + data->tex.wall_x;
	}
	else if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
	{
		data->tex.floor_x = data->ray.map_x + 1.0;
		data->tex.floor_y = data->ray.map_y + data->tex.wall_x;
	}
	else if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
	{
		data->tex.floor_x = data->ray.map_x + data->tex.wall_x;
		data->tex.floor_y = data->ray.map_y;
	}
	else if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
	{
		data->tex.floor_x = data->ray.map_x + data->tex.wall_x;
		data->tex.floor_y = data->ray.map_y + 1.0;
	}
}

void	ray_calc_tex2(t_data *data)
{
	double	current_pos;
	double	weight;

	current_pos = data->screen_heigth
		/ (2 * (double)data->y - data->screen_heigth);
	weight = current_pos / data->ray.wall_dist;
	data->tex.pix_pos_x = weight * data->tex.floor_x + (1.0 - weight)
		* data->cam.pos_x;
	data->tex.pix_pos_y = weight * data->tex.floor_y + (1.0 - weight)
		* data->cam.pos_y;
	data->tex.floor_tex_x = (int)(data->tex.pix_pos_x * data->tex.w)
		% data->tex.w;
	data->tex.floor_tex_y = (int)(data->tex.pix_pos_y * data->tex.h)
		% data->tex.h;
}

void	raycast_floor_ceiling(t_data *data)
{
	ray_texel_pos(data);
	if (data->draw_end < 0)
		data->draw_end = data->screen_heigth;
	data->y = data->draw_end + 1;
	while (data->y < data->screen_heigth)
	{
		ray_calc_tex2(data);
		data->mlx.color = ((unsigned int *)data->spr_tab[1])
		[(data->tex.w * data->tex.floor_tex_y + data->tex.floor_tex_x)];
		my_mlx_pixel_put(data, data->x, data->y, data->mlx.color);
		data->mlx.color = ((unsigned int *)data->spr_tab[0])
		[(data->tex.w * data->tex.floor_tex_y + data->tex.floor_tex_x)];
		my_mlx_pixel_put(data, data->x, data->screen_heigth - data->y - 1,
			data->mlx.color);
		data->y++;
	}
}
