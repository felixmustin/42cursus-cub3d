#include "main.h"

size_t ft_strLen(const char *str) {
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*dst;

	len = ft_strLen(s1);
	dst = malloc (sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

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

int render(t_data *data)
{
    if (data->cam.front || data->cam.back || data->cam.right || data->cam.left || data->cam.rotate || data->cam.display)
    {
        data->x = 0;
        data->y = 0;
        data->cam.display = false;
        move(data, &data->cam);
        while (data->x < data->screen_width)
        {
            raycast_wall(data);
            raycast_floor_ceil(data);
            data->ZBuffer[data->x] = data->ray.wall_dist;
            data->x++;
        }
        draw_sprites(data);
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
    //ft_create_texture(data, );
    ft_create_texture(data);
    ft_create_image(data);
    mlx_hook(data->mlx.mlx_win, ON_KEYDOWN, 1L<<0, ft_key_press, data);
    mlx_hook(data->mlx.mlx_win, ON_KEYUP, 1L<<1, ft_key_release, data);
    mlx_hook(data->mlx.mlx_win, ON_DESTROY, 0, leave, data);

    mlx_loop_hook(data->mlx.mlx_ptr, render, data);
    mlx_loop(data->mlx.mlx_ptr);
}

int main(void)
{
    t_data data;

    data.map = malloc(24 * sizeof(char *));

        data.map[0] = "111111111111111111111111";
        data.map[1] = "100000000000000000000001";
        data.map[2] = "100000000000000000000001";
        data.map[3] = "100000000000000000000001";
        data.map[4] = "100000222220000303030001";
        data.map[5] = "100000200020000000000001";
        data.map[6] = "100000200020000300030001";
        data.map[7] = "100000200020000000000001";
        data.map[8] = "100000220220000303030001";
        data.map[9] = "100000000000000000000001";
        data.map[10] = "100000000000000000000001";
        data.map[11] = "100000000000000000000001";
        data.map[12] = "100000000000000000000001";
        data.map[13] = "100000000000000000000001";
        data.map[14] = "100000000000000000000001";
        data.map[15] = "100000000000000000000001";
        data.map[16] = "100000222220000303030001";
        data.map[17] = "100000200020000000000001";
        data.map[18] = "100000200020000300030001";
        data.map[19] = "100000200020000000000001";
        data.map[20] = "100000220220000303030001";
        data.map[21] = "100000000000000000000001";
        data.map[22] = "100000000000000000000001";
        data.map[23] = "111111111111111111111111";

    data.tex.w = 64;
    data.tex.h = 64;
    data.tex.tex = malloc(sizeof(void *) * 9);
    data.tex.tex_tab = malloc(sizeof(char *) * 9);
    data.tex.textures = malloc(sizeof(char *) * 9);
        data.tex.textures[0] = "textures/wood.xpm";
        data.tex.textures[1] = "textures/floor_1.xpm";
        data.tex.textures[2] = "textures/wall_1.xpm";
        data.tex.textures[3] = "textures/wall_2.xpm";
        data.tex.textures[4] = "textures/wall_3.xpm";
        data.tex.textures[5] = "textures/wall_4.xpm";
        data.tex.textures[6] = "textures/sprite_1.xpm"; //barrel
        data.tex.textures[7] = "textures/sprite_2.xpm"; //hgreenlight
        data.tex.textures[8] = "textures/pillar.xpm";

    data.numSprite = 3;
    data.sprite = malloc(sizeof(t_sprite) * data.numSprite);
    data.sprite[0].x = 20.5;
    data.sprite[0].y = 11.5;
    data.sprite[0].text = 7;
    data.sprite[0].heigth = 16;
    data.sprite[1].x = 18.5;
    data.sprite[1].y = 10.5;
    data.sprite[1].text = 8; 
    data.sprite[1].heigth = 64;
    data.sprite[2].x = 21.5;
    data.sprite[2].y = 1.5;
    data.sprite[2].text = 6; 
    data.sprite[2].heigth = 32;

    data.spriteOrder = malloc(sizeof(int) * data.numSprite);
    data.spriteDistance = malloc(sizeof(double) * data.numSprite);

    data.cam.display = true;
    data.map_width = 24;
    data.map_heigth = 24;
    data.screen_width = 640;
    data.screen_heigth = 480;

    data.ZBuffer = malloc(sizeof(double) * data.screen_width);

    data.cam.pos_x = 22;
    data.cam.pos_y = 11.5;
    data.cam.dir_x = -1;
    data.cam.dir_y = 0;
    data.cam.plane_x = 0;
    data.cam.plane_y = 1;
    data.cam.front = false;
    data.cam.back = false;
    data.cam.right = false;
    data.cam.left = false;
    data.cam.speed = 0.1;
    data.leave = 0;

    //init(&data)
    //parse(&data);
    prepare(&data);
}