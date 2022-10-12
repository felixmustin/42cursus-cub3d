/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_recover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:56 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:24:57 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	**file_to_color(char *file)
{
	char	**str;

	str = file_to_string(file);
	if (!str)
		return (NULL);
	if (ft_strcmp(str[0], "F") != 0 && ft_strcmp(str[0], "C") != 0)
	{
		free_tab(str);
		return (NULL);
	}
	return (str);
}

int	stock_color(char *file, t_data *data)
{
	char	**str;
	int		result;

	result = 1;
	str = file_to_color(file);
	if (!str)
		return (0);
	if ((ft_strcmp(str[0], "C") == 0 && data->floor_color != 0)
		&& (ft_strcmp(str[0], "F") == 0 && data->ceiling_color != 0))
		result = 0;
	if (ft_strcmp(str[0], "F") == 0 && data->floor_color == 0 && result)
	{
		data->floor_color = get_color(str);
		if (data->floor_color == -1)
			result = 0;
	}
	if (ft_strcmp(str[0], "C") == 0 && data->ceiling_color == 0 && result)
	{
		data->ceiling_color = get_color(str);
		if (data->ceiling_color == -1)
			result = 0;
	}
	free_tab(str);
	return (result);
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

int	color_recover(int i, char **file, t_data *data)
{
	i = recup_color(i, file, data);
	if (i == 0)
	{
		printf("Error\n");
		write(1, "error : color information are not correct\n", 42);
		free_texture(data);
		free_tab(file);
		return (0);
	}
	return (i);
}
