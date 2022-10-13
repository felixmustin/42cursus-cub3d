/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_or_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:39:25 by cmillet           #+#    #+#             */
/*   Updated: 2022/10/12 15:39:27 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_line(char *file)
{
	char	**str;

	str = ft_split(file, 32);
	if (!str)
		return (0);
	if (ft_strcmp(str[0], "NO") == 0 || ft_strcmp(str[0], "SO") == 0
		|| ft_strcmp(str[0], "WE") == 0 || ft_strcmp(str[0], "EA") == 0)
	{
		free_tab(str);
		return (1);
	}
	if (ft_strcmp(str[0], "F") == 0 || ft_strcmp(str[0], "C") == 0)
	{
		free_tab(str);
		return (2);
	}
	free_tab(str);
	printf("Error\ninfos are not correct\n");
	return (3);
}

int	texture_or_color(t_data *data, char **file)
{
	int	i;
	int	check;

	i = -1;
	while (file[++i] && (!color_is_full(data) || !texture_is_full(data)))
	{
		if (file[i][0] != '\n' && file[i][0] != '\0')
		{
			check = check_line(file[i]);
			if (!check || check == 3)
				return (0);
			if (check == 1)
				if (!texture_recover(file[i], data))
					return (0);
			if (check == 2)
				if (!color_recover(file[i], data))
					return (0);
		}
	}
	if (!file[i] || (!color_is_full(data) || !texture_is_full(data)))
		return (0);
	return (i);
}
