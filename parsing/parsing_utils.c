#include "../main.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
	}
}

int	ft_strlen_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);	
}

int	malloc_texture(t_data *data)
{
	int	i;

	i = 0;
    data->tex.textures = malloc(sizeof(char *) * 5);
	if (!data->tex.textures)
		return (0);
	data->tex.tex = malloc(sizeof(void *) * 5);
	if (!data->tex.tex)
		return (0);
    data->tex.tex_tab = malloc(sizeof(char *) * 5);
	if (!data->tex.tex_tab)
		return (0);
	data->tex.w = 64;
	data->tex.h = 64;
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}