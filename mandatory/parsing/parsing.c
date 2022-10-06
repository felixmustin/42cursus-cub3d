#include "../main.h"

int	check_ext(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] == 'b')
	{
		i--;
		if (str[i] == 'u')
		{
			i--;
			if (str[i] == 'c')
			{
				i--;
				if (str[i] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	if (ac < 2)
	{
		write(1, "Error, map as first parameter is required\n", 42);
		return (0);
	}
	if (ac > 2)
	{
		write(1, "Error, map is the only parameter required\n", 42);
		return (0);
	}
	if (ac == 2)
	{
		if (!check_ext(av[1]))
		{
			write(1, "map format need to be .cub\n", 27);
			return (0);
		}
	}
	return (1);
}

void	init_data(t_data *data)
{
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->cam.pos_x = 0;
	data->cam.pos_y = 0;
	data->cam.dir_x = 0;
	data->cam.dir_y = 0;
	data->cam.plane_x = 0;
	data->cam.plane_y = 0;
	data->cam.front = false;
	data->cam.back = false;
	data->cam.right = false;
	data->cam.left = false;
	data->cam.display = true;
	data->cam.speed = 0.05;
	data->leave = 0;
	data->map_width = 0;
	data->map_heigth = 0;
	data->screen_width = 640;
	data->screen_heigth = 480;
}

int	parsing(int ac, char **av, t_data *data)
{
	int		i;
	char	**file;

	i = 0;
	file = NULL;
	init_data(data);
	if (!check_arg(ac, av))
		return (0);
	file = file_recover(av[1]);
	if (!file)
		return (0);
	i = texture_recover(file, data, i);
	if (i == 0)
		return (0);
	i = color_recover(i, file, data);
	if (i == 0)
		return (0);
	if (!map_recover(data, file, i))
		return (0);
	free_tab(file);
	if (!parser(data))
		return (0);
	return (1);
}
