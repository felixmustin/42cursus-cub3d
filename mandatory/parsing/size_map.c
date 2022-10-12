/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:25:48 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:25:49 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	get_width(char **map)
{
	size_t	width;
	int		i;

	i = 0;
	width = ft_strlen(map[i]);
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

void	get_size(char **map, int *width, int *height)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	*height = i;
	*width = get_width(map);
}
