/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:27:32 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:27:33 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ray_calc_column(t_data *data)
{
	data->line_height = abs((int)((double)data->screen_heigth
				/ data->ray.wall_dist));
	data->draw_start = -data->line_height / 2
		+ (double)data->screen_heigth / 2;
	data->draw_end = data->line_height / 2
		+ (double)data->screen_heigth / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	if (data->draw_end >= data->screen_heigth)
		data->draw_end = data->screen_heigth - 1;
}

void	ray_calc_tex_pos(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->tex.wall_x = data->ray.ray_pos_y
			+ data->ray.wall_dist * data->ray.ray_dir_y;
	}
	else
	{
		data->tex.wall_x = data->ray.ray_pos_x
			+ data->ray.wall_dist * data->ray.ray_dir_x;
	}	
	data->tex.wall_x -= floor(data->tex.wall_x);
	data->tex.tex_x = (int)(data->tex.wall_x * data->tex.w);
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		data->tex.tex_x = data->tex.w - data->tex.tex_x - 1;
	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		data->tex.tex_x = data->tex.w - data->tex.tex_x - 1;
}

void	raycast_wall(t_data *data)
{
	ray_init(data);
	ray_find_first_inter(data);
	ray_dda(data);
	ray_calc_column(data);
	ray_calc_tex_pos(data);
	data->y = data->draw_start;
	while (data->y < data->draw_end)
	{
		data->tex.tex_y = (int)
			((data->y * 2 - data->screen_heigth + data->line_height)
				* (data->tex.h / 2) / data->line_height);
		if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
			data->color_int = 0;
		else if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
			data->color_int = 1;
		else if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
			data->color_int = 2;
		else if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
			data->color_int = 3;
		data->mlx.color = ((unsigned int *)data->tex.tex_tab[data->color_int])
		[(data->tex.w * data->tex.tex_y + data->tex.tex_x)];
		my_mlx_pixel_put(data, data->x, data->y, data->mlx.color);
		data->y++;
	}
}
