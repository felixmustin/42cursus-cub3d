#include "main.h"

void	size_minimap(t_data *data)
{
	if (data->screen_width < 700 || data->screen_heigth < 700)
		data->sizeminimap = 5;
	else if (data->screen_width < 300 || data->screen_heigth < 300)
		data->sizeminimap = 3;
	else
		data->sizeminimap = 10;
}

int		drawsquare(t_data *data)
{
	int i;
	int v;

	v = 0;
	i = 0;
	while (i < data->sizeminimap)
	{
		while (v < data->sizeminimap)
		{
			if (data->mlx.color != 0)
				my_mlx_pixel_put(data, data->minimap_x + v, data->minimap_y + i, data->mlx.color);
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
	data->mlx.color = 16777215;
	if (c == '1')
		data->mlx.color = 1;
	if ((int)data->cam.pos_x == map_x && (int)data->cam.pos_y == map_y)
		data->mlx.color = 13910590;
	drawsquare(data);
}

void	minimap(t_data *data)
{
	int x;
	int y;

    size_minimap(data);
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