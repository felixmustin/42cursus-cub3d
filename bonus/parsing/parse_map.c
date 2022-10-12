/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:25:19 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:25:21 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	position_player2(t_data *data, char c)
{
	if (c == 'W')
	{
		data->cam.dir_x = -1;
		data->cam.dir_y = 0;
		data->cam.plane_x = 0;
		data->cam.plane_y = -1;
	}
	if (c == 'E')
	{
		data->cam.dir_x = 1;
		data->cam.dir_y = 0;
		data->cam.plane_x = 0;
		data->cam.plane_y = 1;
	}	
}

void	position_player(t_data *data, int x, int y, char c)
{
	data->cam.pos_x = (double)x + 0.5;
	data->cam.pos_y = (double)y + 0.5;
	if (c == 'N')
	{
		data->cam.dir_x = 0;
		data->cam.dir_y = -1;
		data->cam.plane_x = 1;
		data->cam.plane_y = 0;
	}
	if (c == 'S')
	{
		data->cam.dir_x = 0;
		data->cam.dir_y = 1;
		data->cam.plane_x = -1;
		data->cam.plane_y = 0;
	}
	position_player2(data, c);
}

int	check_player(t_data *data, int *player, int i, int j)
{
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1'
				&& data->map[i][j] != 32)
			{
				if ((data->map[i][j] == 'N' || data->map[i][j] == 'S'
					|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
						&& *player == 0)
				{
					*player += 1;
					position_player(data, j, i, data->map[i][j]);
				}
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_enable(t_data *data)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = 0;
	j = 0;
	if (!check_player(data, &player, i, j))
		return (0);
	if (player == 0)
		return (0);
	return (1);
}

int	parse_map(t_data *data)
{
	if (!check_map(data->map))
	{
		printf("Error\n");
		write(1, "error : map is invalid\n", 23);
		return (0);
	}
	if (!map_enable(data))
	{
		printf("Error\n");
		write(1, "error : map is invalid\n", 23);
		return (0);
	}
	get_size(data->map, &data->map_width, &data->map_heigth);
	return (1);
}
