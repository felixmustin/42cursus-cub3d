#include "../main.h"

int	check_xpm(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'm')
	{
		i--;
		if (str[i] == 'p')
		{
			i--;
			if (str[i] == 'x')
			{
				i--;
				if (str[i] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int	check_extension(t_data *data)
{
	int	i;

	i = 0;
	while (data->tex.textures[i] != NULL)
	{
		if (ft_strlen(data->tex.textures[i]) < 4)
			return (0);
		if (!check_xpm(data->tex.textures[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_acces(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->tex.textures[i] != NULL)
	{
		fd = open(data->tex.textures[i], O_RDONLY);
		if (fd <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	parse_texture(t_data *data)
{
	if (!check_extension(data))
	{
		write(1, "error : texture are not .xpm\n", 29);
		return (0);
	}
	if (!check_acces(data))
	{
		write(1, "error : texture files are not valid\n", 36);
		return (0);
	}
	return (1);
}
