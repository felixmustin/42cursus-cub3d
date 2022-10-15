/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:26:28 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:26:29 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	drawsquare(t_data *data)
{
	int	i;
	int	v;

	v = 0;
	i = 0;
	while (i < data->sizeminimap)
	{
		while (v < data->sizeminimap)
		{
			if (data->mlx.color != 0)
			{
				my_mlx_pixel_put(data, data->minimap_x + v,
					data->minimap_y + i, data->mlx.color);
			}
			v++;
		}
		v = 0;
		i++;
	}
	data->minimap_x += data->sizeminimap;
	return (0);
}

void	checkbox(t_data *data, char c, int map_x, int map_y)
{
	data->mlx.color = 0;
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		data->mlx.color = 0xFFFFFF;
	if (c == '1')
		data->mlx.color = 1;
	if ((int)data->cam.pos_x == map_x && (int)data->cam.pos_y == map_y)
		data->mlx.color = 13910590;
	drawsquare(data);
}

void	minimap(t_data *data)
{
	int	x;
	int	y;

	data->sizeminimap = 10;
	if (data->map_heigth > 50 || data->map_width > 50)
		data->sizeminimap = 3;
	x = 0;
	y = 0;
	data->minimap_x = 0;
	data->minimap_y = 0;
	while (y < data->map_heigth)
	{
		while (data->map[y][x])
		{
			checkbox(data, data->map[y][x], x, y);
			x++;
		}
		y++;
		x = 0;
		data->minimap_y = data->sizeminimap * y;
		data->minimap_x = 0;
	}
}
