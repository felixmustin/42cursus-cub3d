/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:28:23 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:28:24 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parser(t_data *data)
{
	if (!parse_texture(data))
	{
		free_tab(data->map);
		free_texture(data);
		return (0);
	}
	if (!parse_map(data))
	{
		free_tab(data->map);
		free_texture(data);
		return (0);
	}
	return (1);
}
