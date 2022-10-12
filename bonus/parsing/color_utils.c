/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:27:54 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:27:54 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		free_tab(split_color);
		return (0);
	}
	check_color(split_color, &i);
	if (i == 3)
	{
		color = (pow(256, 2) * ft_atoi(split_color[0])) + \
			(256 * ft_atoi(split_color[1])) + ft_atoi(split_color[2]);
	}
	free_tab(split_color);
	return (color);
}

char	*split_to_string(char **split)
{
	int		i;
	char	*str;
	char	*str1;

	i = 2;
	str = ft_strdup(split[1]);
	while (split[i])
	{
		str1 = ft_strjoin(str, split[i]);
		free(str);
		str = ft_strdup(str1);
		free(str1);
		i++;
	}
	return (str);
}

char	**file_to_string(char *file)
{
	char	**str;
	char	**split;

	split = NULL;
	str = ft_split(file, 32);
	if (ft_strlen_split(str) > 2)
	{
		split = malloc(sizeof(char *) * 3);
		if (!split)
			return (NULL);
		split[0] = ft_strdup(str[0]);
		split[1] = split_to_string(str);
		split[2] = NULL;
		free_tab(str);
		return (split);
	}
	return (str);
}
