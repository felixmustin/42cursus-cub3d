
#include "main.h"

void init_cursor(t_data *d)
{
    my_mlx_pixel_put(d, d->screen_width/2 - 5, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2 - 6, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2 - 7, d->screen_heigth/2, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2 - 8, d->screen_heigth/2, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2 - 9, d->screen_heigth/2, 0xF12B00);
    //my_mlx_pixel_put(d, d->screen_width/2 - 10, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2 + 5, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2 + 6, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2 + 7, d->screen_heigth/2, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2 + 8, d->screen_heigth/2, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2 + 9, d->screen_heigth/2, 0xF12B00);
    //my_mlx_pixel_put(d, d->screen_width/2 + 10, d->screen_heigth/2, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 5, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 6, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 7, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 8, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 9, 0xF12B00);
    //my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 - 10, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 5, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 6, 0xF12B00);
    my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 7, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 8, 0xF12B00);
    // my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 9, 0xF12B00);
    //my_mlx_pixel_put(d, d->screen_width/2, d->screen_heigth/2 + 10, 0xF12B00);
}
