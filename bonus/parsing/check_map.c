/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:52 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:24:53 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	empty_line(char *str)
{
	int	i;
	int	empty;

	i = 0;
	empty = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32 && str[i] != '\n')
			empty++;
		i++;
	}
	return (empty);
}

int	check_right_and_left(char *str, int i)
{
	int	j;
	int	k;

	j = i;
	k = i;
	while (str[j] != '\0' && str[j] != '1' && str[j] != 32)
		j++;
	while (k >= 0 && str[k] != '1' && str[k] != 32)
		k--;
	if (k >= 0 && str[j] == '1' && str[k] == '1')
		return (1);
	return (0);
}

int	check_up_and_down(char **str, int i, int j)
{
	int	k;
	int	l;

	k = i;
	l = i;
	while (str[k] != NULL && str[k][j] && str[k][j] != '1' && str[k][j] != 32)
		k++;
	while (l >= 0 && str[l][j] != '1' && str[l][j] != 32)
		l--;
	if (l >= 0 && str[k][j] == '1' && str[l][j] == '1')
		return (1);
	return (0);
}

int	check_border(char **str, int i, int j)
{
	if (!check_right_and_left(str[i], j))
		return (0);
	if (!check_up_and_down(str, i, j))
		return (0);
	return (1);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		if (!empty_line(map[i]))
			return (0);
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				if (!check_border(map, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}
