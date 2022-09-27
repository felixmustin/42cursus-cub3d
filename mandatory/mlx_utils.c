#include "main.h"

void	my_mlx_pixel_put(t_data *data, int xx, int yy, int color)
{
	char	*offset;

	offset = data->mlx.addr + (yy * (data->mlx.line_length)
				+ xx * (data->mlx.bits_per_pixel / 8));
    *(unsigned int*)offset = color;
}

void	ft_create_image(t_data *data)
{
    data->mlx.mlx_img = mlx_new_image(data->mlx.mlx_ptr, data->screen_width, data->screen_heigth);
    data->mlx.addr = mlx_get_data_addr(data->mlx.mlx_img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
}

void ft_create_texture(t_data *data) 
{
    int i = 0;
    
    while (i < 4) {
        data->tex.tex[i] = mlx_xpm_file_to_image(data->mlx.mlx_ptr, data->tex.textures[i], &data->tex.w, &data->tex.h);
        data->tex.tex_tab[i] = mlx_get_data_addr(data->tex.tex[i], &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
        i++;
    }
}

void	ft_clear_window(t_data *data)
{
    mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
    //mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.mlx_img);
    //mlx_destroy_image(data->mlx.mlx_ptr, data->tex.tex);
}