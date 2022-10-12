/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:28:59 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:29:01 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_texture(t_data *data)
{
	int	i;

	i = 0;
	free_tab(data->tex.textures);
	free(data->tex.tex_tab);
	free(data->tex.tex);
}

char	*ft_strdup_modif(char *str, char c)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dst)
		return (0);
	while (str[i] != '\0' && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**file_to_texture(char *file)
{
	char	**str;

	str = ft_split(file, 32);
	if (!str)
		return (NULL);
	if (ft_strcmp(str[0], "NO") != 0 && ft_strcmp(str[0], "SO") != 0
		&& ft_strcmp(str[0], "WE") != 0 && ft_strcmp(str[0], "EA") != 0)
	{
		free_tab(str);
		printf("Error\n");
		printf("infos about texture are not correct");
		return (NULL);
	}
	return (str);
}
