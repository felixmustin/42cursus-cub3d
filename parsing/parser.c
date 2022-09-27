#include "../mandatory/main.h"

int	parser(t_data *data)
{
	if (!parse_texture(data))
		return (0);
	if (!parse_map(data))
		return (0);
	return (1);
}