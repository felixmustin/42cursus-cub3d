#include "main.h"

void color_floor_ceiling(t_data *data)
{
    if (data->draw_end < 0)
        data->draw_end = data->screen_heigth;
    data->y=data->draw_end;
    while (data->y < data->screen_heigth)
    {
        my_mlx_pixel_put(data, data->x, data->y, data->floor_color);
        my_mlx_pixel_put(data, data->x, data->screen_heigth-data->y-1, data->ceiling_color);
        data->y++;
    }
}