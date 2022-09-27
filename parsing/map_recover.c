#include "../mandatory/main.h"

int	map_size(char **file, int i)
{
	int	size;

	size = 0;
	while (file[i] != NULL)
	{
		if (file[i][0] != '\n')
			size++;
		i++;
	}
	return (size);
}

int	malloc_map(t_data *data, int i, char **file)
{
	int	size;

	size = map_size(file, i);
	if (size == 0)
		return (0);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		return (0);
	return (1);
}

int	recup_map(t_data *data, char **file, int i)
{
	int	j;

	j = 0;
	if (!malloc_map(data, i, file))
		return (0);
	while (file[i] != NULL)
	{
		if (file[i] != NULL && file[i][0] != '\n')
		{
			data->map[j] = ft_strdup_modif(file[i], '\n');
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
	return (1);
}

int	map_recover(t_data *data, char **file, int i)
{
	if (!recup_map(data, file, i))
		return (0);
	return (1);
}