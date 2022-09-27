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

void replace_mouse(t_data *data)
{
    mlx_mouse_move(data->mlx.mlx_win, data->screen_width/2, data->screen_heigth/2);
    mlx_mouse_hide();
}

void display_menu(t_data *data)
{
    if (data->menu == false)
    {
        data->menu = true;
        data->cam.front = false;
		data->cam.back = false;
		data->cam.left = false;
		data->cam.right = false;
        data->cam.rotate = false;
        mlx_mouse_show();
        mlx_string_put(data->mlx.mlx_ptr, data->mlx.mlx_win, data->screen_width/2 - 20, data->screen_heigth/2, 0xFFFFFF, "Pause");
        data->cam.display = false;
    }
    else if (data->menu == true)
    {
        data->menu = false;
        replace_mouse(data);
        data->cam.display = true;
    }
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
            raycast_floor_ceiling(data);
            data->sprite.ZBuffer[data->x] = data->ray.wall_dist;
            data->x++;
        }
        draw_sprites(data);
        minimap(data);
        init_cursor(data);
        data->cam.display = true;
    }
    if (data->leave)
        leave(data);
    else if (!data->menu)
        mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.mlx_img, 0, 0);
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

    replace_mouse(data);
    mlx_hook(data->mlx.mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);

    mlx_loop_hook(data->mlx.mlx_ptr, render, data);
    mlx_loop(data->mlx.mlx_ptr);
}

void init_bonus(t_data *data)
{
    data->sprite.numSprite = 3;

    data->sprite.Sprites = malloc(sizeof(char *) * (data->sprite.numSprite + 2));
        data->sprite.Sprites[0] = "textures/purplestone.xpm";
        data->sprite.Sprites[1] = "textures/wood.xpm";
        data->sprite.Sprites[2] = "textures/sprite_1.xpm"; //barrel
        data->sprite.Sprites[3] = "textures/sprite_2.xpm"; //hgreenlight
        data->sprite.Sprites[4] = "textures/pillar.xpm";
    data->sprite.spr_tab = malloc(sizeof(char *) * (data->sprite.numSprite + 2));
    data->sprite.spr = malloc(sizeof(void *) * (data->sprite.numSprite + 2));
    data->sprite_info = malloc(sizeof(t_sprite_info) *data->sprite.numSprite);
    data->sprite.spriteOrder = malloc(sizeof(int) *data->sprite.numSprite);
    data->sprite.spriteDistance = malloc(sizeof(double) *data->sprite.numSprite);

    data->sprite_info[0].x = 20.5;
    data->sprite_info[0].y = 11.5;
    data->sprite_info[0].text = 3;
    data->sprite_info[0].walkable = 1;
    data->sprite_info[1].x = 18.5;
    data->sprite_info[1].y = 10.5;
    data->sprite_info[1].text = 4; 
    data->sprite_info[1].walkable = 0;
    data->sprite_info[2].x = 21.5;
    data->sprite_info[2].y = 1.5;
    data->sprite_info[2].text = 2; 
    data->sprite_info[2].walkable = 0;
}

int main(int argc, char **argv)
{
    t_data data;

    parsing(argc, argv, &data);

    init_bonus(&data);
    data.sprite.ZBuffer = malloc(sizeof(double) *data.screen_width);
    prepare(&data);
}