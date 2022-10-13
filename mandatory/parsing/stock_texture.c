/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:14:16 by cmillet           #+#    #+#             */
/*   Updated: 2022/10/13 17:14:19 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	stock_texture3(t_data *data, char **str)
{
	if (ft_strcmp(str[0], "EA") == 0 && data->tex.textures[3] == NULL)
	{	
		data->tex.textures[3] = ft_strdup_modif(str[1], '\n');
		if (!data->tex.textures[3])
		{
			free_tab(str);
			return (0);
		}
	}
	return (1);
}

int	stock_texture2(t_data *data, char **str)
{
	if (ft_strcmp(str[0], "SO") == 0 && data->tex.textures[1] == NULL)
	{
		data->tex.textures[1] = ft_strdup_modif(str[1], '\n');
		if (!data->tex.textures[1])
		{
			free_tab(str);
			return (0);
		}
	}
	if (ft_strcmp(str[0], "WE") == 0 && data->tex.textures[2] == NULL)
	{
		data->tex.textures[2] = ft_strdup_modif(str[1], '\n');
		if (!data->tex.textures[2])
		{
			free_tab(str);
			return (0);
		}
	}
	if (!stock_texture3(data, str))
		return (0);
	return (1);
}

int	stock_texture(char *file, t_data *data)
{
	char	**str;

	str = file_to_texture(file);
	if (!str)
		return (0);
	if (!texture_already_fill(str, data))
	{
		printf("Error\n");
		printf("infos about texture are not correct\n");
		free_tab(str);
		return (0);
	}
	if (ft_strcmp(str[0], "NO") == 0 && data->tex.textures[0] == NULL)
	{
		data->tex.textures[0] = ft_strdup_modif(str[1], '\n');
		if (!data->tex.textures[0])
		{
			free_tab(str);
			return (0);
		}
	}
	if (!stock_texture2(data, str))
		return (0);
	free_tab(str);
	return (1);
}
