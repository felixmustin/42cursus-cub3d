#include "../main.h"

int	check_border2(char **map, int y, int i)
{
	int yb;
	int ib;

	yb = 0;
	ib = 0;
	while (map[y][ib] != '\0')
	{
		if (map[y][ib] != '1')
			return (0);
		ib++;
	}
	while (map[yb] != NULL)
	{
		if (map[yb][i] != '1')
			return (0);
		yb++;
	}
	return (1);
}

int	check_border(char **map, int *width, int *height)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map[0][i] != '\0')
	{
		if (map[0][i] != '1')
			return (0);
		i++;
		*width +=1;
	}
	while (map[y] != NULL)
	{
		if (map[y][0] != '1')
			return (0);
		y++;
		*height += 1;
	}
	if (!check_border2(map, y - 1, i - 1))
		return (0);
	return (1);
}

void	position_player(t_data *data, int x, int y, char c)
{
	data->cam.pos_x = x;
	data->cam.pos_y = y;
	if (c == 'N')
	{
		data->cam.dir_x = 0;
		data->cam.dir_y = 1;
	}
	if (c == 'S')
	{
		data->cam.dir_x = 0;
		data->cam.dir_y = -1;
	}
	if (c == 'W')
	{
		data->cam.dir_x = -1;
		data->cam.dir_y = 0;
	}
	if (c == 'E')
	{
		data->cam.dir_x = 1;
		data->cam.dir_y = 0;
	}
}

int	check_player(t_data *data, int *player)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1')
			{
				if ((data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W') 
						&& *player == 0)
				{
					*player += 1;
					position_player(data, j, i, data->map[i][j]);
				}
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_enable(t_data *data)
{
	int	player;

	player = 0;
	if (!check_player(data, &player))
		return (0);
	if (player == 0)
		return (0);
	return (1);
}

int	parse_map(t_data *data)
{
	if (!check_border(data->map, &data->map_width, &data->map_heigth))
	{
		write(1, "error : map is invalid\n", 23);
		return (0);
	}
	if (!map_enable(data))
	{
		write(1, "error : map is invalid\n", 23);
		return (0);
	}
	return (1);
}