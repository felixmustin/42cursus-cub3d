#include "main.h"


void sortSprites(t_data *data) 
{
    t_sprite_sort sprites[data->numSprite];
    int i;
    int j;
    double tmp;
    int itmp;
    i = -1;
    while(++i < data->numSprite)
    {
        sprites[i].dist = data->spriteDistance[i];
        sprites[i].ord = data->spriteOrder[i];
    }
    i = -1;
    while(++i < data->numSprite)
    {
        j = i + 1;
        while (j < data->numSprite)
        {
            if (sprites[i].dist > sprites[j].dist)
            {
                tmp = sprites[i].dist;
                sprites[i].dist = sprites[j].dist;
                sprites[j].dist = tmp;
                itmp = sprites[i].ord;
                sprites[i].ord = sprites[j].ord;
                sprites[j].ord = itmp;
            }
            j++;
        }
    }
    i = -1;
    while (++i < data->numSprite)
    {
        data->spriteDistance[i] = sprites[data->numSprite - i - 1].dist;
        data->spriteOrder[i] =  sprites[data->numSprite - i - 1].ord;
    }
}


void draw_sprite_calc(t_data *data, int i)
{
    //translate sprite position to relative to camera
    data->spriteX = data->sprite[data->spriteOrder[i]].x - data->cam.pos_x;
    data->spriteY = data->sprite[data->spriteOrder[i]].y - data->cam.pos_y;

    data->invDet = 1.0 / (data->cam.plane_x*data->cam.dir_y - data->cam.dir_x*data->cam.plane_y);
    data->transformX = data->invDet * (data->cam.dir_y*data->spriteX - data->cam.dir_x*data->spriteY);
    data->transformY = data->invDet * (-data->cam.plane_y*data->spriteX + data->cam.plane_x*data->spriteY);
    data->spriteScreenX = (int)((data->screen_width / 2) * (1 + data->transformX / data->transformY));

    data->spriteHeigth = abs((int)(data->screen_heigth / data->transformY));
    data->drawStartY = -data->spriteHeigth / 2 + data->screen_heigth / 2;
    if (data->drawStartY < 0)
        data->drawStartY = 0;
    data->drawEndY = data->spriteHeigth / 2 + data->screen_heigth / 2;
    if (data->drawEndY >= data->screen_heigth)
        data->drawEndY = data->screen_heigth - 1;
    data->spriteWidth = abs((int)(data->screen_heigth / data->transformY));
    data->drawStartX = -data->spriteWidth / 2 + data->spriteScreenX;
    if (data->drawStartX < 0)
        data->drawStartX = 0;
    data->drawEndX = data->spriteWidth / 2 + data->spriteScreenX;
    if (data->drawEndX >= data->screen_width)
        data->drawEndX = data->screen_width - 1;
}

void draw_sprite_do(t_data *data, int i)
{
    i = -1;
    while (++i < data->numSprite)
    {
        draw_sprite_calc(data, i);
        data->stripe = data->drawStartX;
        while (data->stripe < data->drawEndX)
        {
            data->texX = (int)(256 * (data->stripe - (-data->spriteWidth / 2 + data->spriteScreenX)) * data->tex.w / data->spriteWidth) / 256;
            if(data->transformY > 0 && data->stripe > 0 && data->stripe < data->screen_width && data->transformY < data->ZBuffer[data->stripe])
            data->stripe_y = data->drawStartY;
            while(data->stripe_y < data->drawEndY) //for every pixel of the current stripe
            {
                data->d = (data->stripe_y) * 256 - data->screen_heigth * 128 + data->spriteHeigth * 128; //256 and 128 factors to avoid floats
                data->texY = ((data->d * data->tex.h) / data->spriteHeigth) / 256;                        
                data->mlx.color = ((unsigned int*)data->tex.tex_tab[data->sprite[data->spriteOrder[i]].text])[(data->tex.w * data->texY + data->texX)];
                if((data->mlx.color & 0x00FFFFFF) != 0) //paint pixel if it isn't black, black is the invisible color
                    my_mlx_pixel_put(data, data->stripe, data->stripe_y, data->mlx.color);
                data->stripe_y++;
            }
            data->stripe++;
        }
    }
}

void draw_sprites(t_data *data)
{
    int i;

    i = 0;
    while (i < data->numSprite)
    {
        data->spriteOrder[i] = i;
        data->spriteDistance[i] = ((data->cam.pos_x - data->sprite[i].x) * (data->cam.pos_x - data->sprite[i].x) + (data->cam.pos_y - data->sprite[i].y) * (data->cam.pos_y - data->sprite[i].y));
        i++;
    }
    sortSprites(data);
    draw_sprite_do(data, i);
}
