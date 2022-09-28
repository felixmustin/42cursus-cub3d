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
