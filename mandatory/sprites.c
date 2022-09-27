#include "main.h"


void sortSprites(t_data *d) 
{
    t_sprite_sort sprites[d->sprite.numSprite];
    int i;
    int j;
    double tmp;
    int itmp;
    i = -1;
    while(++i < d->sprite.numSprite)
    {
        sprites[i].dist = d->sprite.spriteDistance[i];
        sprites[i].ord = d->sprite.spriteOrder[i];
    }
    i = -1;
    while(++i < d->sprite.numSprite)
    {
        j = i + 1;
        while (j < d->sprite.numSprite)
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
    while (++i < d->sprite.numSprite)
    {
        d->sprite.spriteDistance[i] = sprites[d->sprite.numSprite - i - 1].dist;
        d->sprite.spriteOrder[i] =  sprites[d->sprite.numSprite - i - 1].ord;
    }
}


void draw_sprite_calc(t_data *d, int i)
{
    //translate sprite position to relative to camera
    d->sprite.spriteX = d->sprite_info[d->sprite.spriteOrder[i]].x - d->cam.pos_x;
    d->sprite.spriteY = d->sprite_info[d->sprite.spriteOrder[i]].y - d->cam.pos_y;
    d->sprite.invDet = 1.0 / (d->cam.plane_x*d->cam.dir_y - d->cam.dir_x*d->cam.plane_y);
    d->sprite.transformX = d->sprite.invDet * (d->cam.dir_y*d->sprite.spriteX - d->cam.dir_x*d->sprite.spriteY);
    d->sprite.transformY = d->sprite.invDet * (-d->cam.plane_y*d->sprite.spriteX + d->cam.plane_x*d->sprite.spriteY);
    d->sprite.spriteScreenX = (int)((d->screen_width / 2) * (1 + d->sprite.transformX / d->sprite.transformY));
    d->sprite.spriteHeigth = abs((int)(d->screen_heigth / d->sprite.transformY));
    d->sprite.drawStartY = -d->sprite.spriteHeigth / 2 + d->screen_heigth / 2;
    if (d->sprite.drawStartY < 0)
        d->sprite.drawStartY = 0;
    d->sprite.drawEndY = d->sprite.spriteHeigth / 2 + d->screen_heigth / 2;
    if (d->sprite.drawEndY >= d->screen_heigth)
        d->sprite.drawEndY = d->screen_heigth - 1;
    d->sprite.spriteWidth = abs((int)(d->screen_heigth / d->sprite.transformY));
    d->sprite.drawStartX = -d->sprite.spriteWidth / 2 + d->sprite.spriteScreenX;
    if (d->sprite.drawStartX < 0)
        d->sprite.drawStartX = 0;
    d->sprite.drawEndX = d->sprite.spriteWidth / 2 + d->sprite.spriteScreenX;
    if (d->sprite.drawEndX >= d->screen_width)
        d->sprite.drawEndX = d->screen_width - 1;
}

void draw_sprite_do(t_data *d, int i)
{
    i = -1;
    while (++i < d->sprite.numSprite)
    {
        draw_sprite_calc(d, i);
        d->sprite.stripe = d->sprite.drawStartX;
        while (d->sprite.stripe < d->sprite.drawEndX)
        {
            d->sprite.texX = (int)(256 * (d->sprite.stripe - (-d->sprite.spriteWidth / 2 + d->sprite.spriteScreenX))
                * d->tex.w / d->sprite.spriteWidth) / 256;
            if(d->sprite.transformY > 0 && d->sprite.stripe > 0 && d->sprite.stripe < d->screen_width
                && d->sprite.transformY < d->sprite.ZBuffer[d->sprite.stripe])
            d->sprite.stripe_y = d->sprite.drawStartY;
            while(d->sprite.stripe_y < d->sprite.drawEndY) //for every pixel of the current stripe
            {
                d->sprite.d = (d->sprite.stripe_y) * 256 - d->screen_heigth * 128 + d->sprite.spriteHeigth * 128; //256 and 128 factors to avoid floats
                d->sprite.texY = ((d->sprite.d * d->tex.h) / d->sprite.spriteHeigth) / 256;                        
                d->mlx.color = ((unsigned int*)d->tex.tex_tab[d->sprite_info[d->sprite.spriteOrder[i]].text])[(d->tex.w * d->sprite.texY + d->sprite.texX)];
                if((d->mlx.color & 0x00FFFFFF) != 0) //paint pixel if it isn't black, black is the invisible color
                    my_mlx_pixel_put(d, d->sprite.stripe, d->sprite.stripe_y, d->mlx.color);
                d->sprite.stripe_y++;
            }
            d->sprite.stripe++;
        }
    }
}

void draw_sprites(t_data *d)
{
    int i;

    i = 0;
    while (i < d->sprite.numSprite)
    {
        d->sprite.spriteOrder[i] = i;
        d->sprite.spriteDistance[i] = ((d->cam.pos_x - d->sprite_info[i].x) * (d->cam.pos_x - d->sprite_info[i].x)
            + (d->cam.pos_y - d->sprite_info[i].y) * (d->cam.pos_y - d->sprite_info[i].y));
        i++;
    }
    sortSprites(d);
    draw_sprite_do(d, i);
}
