#include "main.h"

void ft_free(t_data *data)
{
    int i;

    i = 0;
    while (i < 24) {
        //free(data->map[i]);
        i++;
    }
    free(data->map);
    /*free(data->tex.tex);
    free(data->tex.tex_tab);
    free(data->tex.textures);
    free(data->sprite);
    free(data->spriteDistance);
    free(data->spriteOrder);
    free(data->ZBuffer);*/
}

int leave(t_data *data)
{
    ft_clear_window(data);
    ft_free(data);
    exit (1);
}

void init_cursor(t_data *data)
{
    my_mlx_pixel_put(data, 315, 240, 0xF12B00);
    my_mlx_pixel_put(data, 314, 240, 0xF12B00);
    my_mlx_pixel_put(data, 313, 240, 0xF12B00);
    my_mlx_pixel_put(data, 312, 240, 0xF12B00);
    my_mlx_pixel_put(data, 311, 240, 0xF12B00);
    my_mlx_pixel_put(data, 310, 240, 0xF12B00);
    my_mlx_pixel_put(data, 325, 240, 0xF12B00);
    my_mlx_pixel_put(data, 326, 240, 0xF12B00);
    my_mlx_pixel_put(data, 327, 240, 0xF12B00);
    my_mlx_pixel_put(data, 328, 240, 0xF12B00);
    my_mlx_pixel_put(data, 329, 240, 0xF12B00);
    my_mlx_pixel_put(data, 330, 240, 0xF12B00);
    my_mlx_pixel_put(data, 320, 235, 0xF12B00);
    my_mlx_pixel_put(data, 320, 234, 0xF12B00);
    my_mlx_pixel_put(data, 320, 233, 0xF12B00);
    my_mlx_pixel_put(data, 320, 232, 0xF12B00);
    my_mlx_pixel_put(data, 320, 231, 0xF12B00);
    my_mlx_pixel_put(data, 320, 230, 0xF12B00);
    my_mlx_pixel_put(data, 320, 245, 0xF12B00);
    my_mlx_pixel_put(data, 320, 246, 0xF12B00);
    my_mlx_pixel_put(data, 320, 247, 0xF12B00);
    my_mlx_pixel_put(data, 320, 248, 0xF12B00);
    my_mlx_pixel_put(data, 320, 249, 0xF12B00);
    my_mlx_pixel_put(data, 320, 250, 0xF12B00);
}


int render(t_data *data)
{
    //if (data->cam.front || data->cam.back || data->cam.right || data->cam.left || data->cam.rotate || data->cam.display )
    if (data->cam.display)
    {
        data->cam.display = false;
        data->x = 0;
        data->y = 0;
        move(data, &data->cam);
        while (data->x < data->screen_width)
        {
            raycast_wall(data);
            raycast_floor_ceil(data);
            data->ZBuffer[data->x] = data->ray.wall_dist;
            data->x++;
        }
        draw_sprites(data);
        minimap(data);
        init_cursor(data);
        data->cam.display = true;
    }
    if (!data->leave)
        mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.mlx_img, 0, 0);
    else
        leave(data);
    return(1);
}


void prepare(t_data *data)
{
    data->mlx.mlx_ptr = mlx_init();
    data->mlx.mlx_win = mlx_new_window(data->mlx.mlx_ptr, data->screen_width, data->screen_heigth, "cub3d");
    ft_create_texture(data);
    ft_create_image(data);
    mlx_hook(data->mlx.mlx_win, ON_KEYDOWN, 1L<<0, ft_key_press, data);
    mlx_hook(data->mlx.mlx_win, ON_KEYUP, 1L<<1, ft_key_release, data);
    mlx_hook(data->mlx.mlx_win, ON_DESTROY, 0, leave, data);

    mlx_mouse_move(data->mlx.mlx_win, data->screen_width/2, data->screen_heigth/2);
    mlx_mouse_hide();

    mlx_hook(data->mlx.mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);

    mlx_loop_hook(data->mlx.mlx_ptr, render, data);
    mlx_loop(data->mlx.mlx_ptr);
}

int main(int ac, char **av)
{
    t_data data;

	parsing(ac, av, &data);
    //init(&data)
    //parse(&data);
    prepare(&data);
}