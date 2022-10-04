#include "main.h"

void	init_cursor(t_data *d)
{
	int	c;

	c = 0xF12B00;
	my_mlx_pixel_put(d, d->screen_width / 2 - 5, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2 - 6, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2 - 7, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2 + 5, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2 + 6, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2 + 7, d->screen_heigth / 2, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 - 5, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 - 6, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 - 7, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 + 5, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 + 6, c);
	my_mlx_pixel_put(d, d->screen_width / 2, d->screen_heigth / 2 + 7, c);
}
