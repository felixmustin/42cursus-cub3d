#include "../main.h"

void	check_color(char **split_color, int *i)
{
	int	color_value;

	color_value = 0;
	while (*i < ft_strlen_split(split_color))
	{
		color_value = ft_atoi(split_color[*i]);
		if (color_value <= 255 && color_value >= 0)
			*i += 1;
		else
			break ;
	}
}

int	get_color(char	**str)
{
	char	**split_color;
	int		i;
	int		color;

	i = 0;
	color = -1;
	split_color = ft_split(str[1], ',');
	if (!split_color)
		return (0);
	if (ft_strlen_split(split_color) != 3)
		return (0);
	check_color(split_color, &i);
	if (i == 3)
	{
		color = (pow(256, 2) * ft_atoi(split_color[0])) + \
			(256 * ft_atoi(split_color[1])) + ft_atoi(split_color[2]);
	}
	return (color);
}

char	**file_to_color(char *file)
{
	char	**str;

	str = ft_split(file, 32);
	if (!str)
		return (NULL);
	if (ft_strcmp(str[0] ,"F") != 0 && ft_strcmp(str[0] ,"C") != 0)
		return (NULL);
	return (str);
}

int	stock_color(char *file, t_data *data)
{
	char	**str;

	str = file_to_color(file);
	if (!str)
		return (0);
	if ((ft_strcmp(str[0], "C") == 0 && data->floor_color != 0) && (ft_strcmp(str[0] ,"F") == 0 && data->ceiling_color != 0))
		return (0);
	if (ft_strcmp(str[0] ,"F") == 0 && data->floor_color == 0)
	{
		data->floor_color = get_color(str);
		if (data->floor_color == -1)
			return (0);
	}
	if (ft_strcmp(str[0], "C") == 0 && data->ceiling_color == 0)
	{
		data->ceiling_color = get_color(str);
		if (data->ceiling_color == -1)
			return (0);
	}
	return (1);
}

int	color_is_full(t_data *data)
{
	if (data->ceiling_color > 0 && data->floor_color > 0)
		return (1);
	else
		return (0);
}

int	recup_color(int i, char **file, t_data *data)
{
	while (file[i] != NULL && !color_is_full(data))
	{
		if (file[i] && file[i][0] != '\n' && file[i][0] != '\0')
			if (!stock_color(file[i], data))
				return (0);
		i++;
	}
	return (i);
}

int	color_recover(int	i, char **file, t_data *data)
{
	i = recup_color(i, file, data);
	if (i == 0)
		return (0);
	return (i);
}