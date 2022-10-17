/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:22:48 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/17 12:22:50 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	**fill_color(char **str)
{
	char	**split;

	split = malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	split[0] = ft_strdup(str[0]);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	split[1] = split_to_string(str);
	if (!split[1])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	split[2] = NULL;
	return (split);
}
