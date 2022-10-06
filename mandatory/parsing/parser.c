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
