#include "main.h"

void ray_init(t_data *data)
{
    //init value
    data->ray.cam_x = (2*(double)data->x/(double)data->screen_width) - 1;
    data->ray.rayPos_x = data->cam.pos_x;
    data->ray.rayPos_y = data->cam.pos_y;
    data->ray.rayDir_x = data->cam.dir_x + data->cam.plane_x*data->ray.cam_x;
    data->ray.rayDir_y = data->cam.dir_y + data->cam.plane_y*data->ray.cam_x;
    data->ray.map_x = (int)data->ray.rayPos_x;
    data->ray.map_y = (int)data->ray.rayPos_y;
    data->ray.deltaDist_x = sqrt(1+(data->ray.rayDir_y*data->ray.rayDir_y)/(data->ray.rayDir_x*data->ray.rayDir_x));
    data->ray.deltaDist_y = sqrt(1+(data->ray.rayDir_x*data->ray.rayDir_x)/(data->ray.rayDir_y*data->ray.rayDir_y));
    data->ray.hit = 0;
}

void ray_find_first_inter(t_data *data)
{
    if (data->ray.rayDir_x < 0) {
        data->ray.step_x = -1;
        data->ray.sideDist_x = (data->ray.rayPos_x - data->ray.map_x) * data->ray.deltaDist_x;
    }
    else {
        data->ray.step_x = 1;
        data->ray.sideDist_x = (data->ray.map_x + 1 - data->ray.rayPos_x) * data->ray.deltaDist_x;
    }
    if (data->ray.rayDir_y < 0) {
        data->ray.step_y = -1;
        data->ray.sideDist_y = (data->ray.rayPos_y - data->ray.map_y) * data->ray.deltaDist_y;
    }
    else {
        data->ray.step_y = 1;
        data->ray.sideDist_y = (data->ray.map_y + 1 - data->ray.rayPos_y) * data->ray.deltaDist_y;
    }
}

void ray_DDA(t_data *data)
{
    while (data->ray.hit == 0)
    {
        if (data->ray.sideDist_x < data->ray.sideDist_y)
        {
            data->ray.sideDist_x += data->ray.deltaDist_x;
            data->ray.map_x += data->ray.step_x;
            data->ray.side = 0;
        }
        else
        {
            data->ray.sideDist_y += data->ray.deltaDist_y;
            data->ray.map_y += data->ray.step_y;
            data->ray.side = 1;
        }
        if (data->map[(int)data->ray.map_y][(int)data->ray.map_x] > 48)
            data->ray.hit = 1;
    }
    //distance perpandicular to camera plane
    if (data->ray.side == 0)
        data->ray.wall_dist = fabs((data->ray.map_x-data->cam.pos_x+(1-data->ray.step_x)/2)/data->ray.rayDir_x);
    else 
        data->ray.wall_dist = fabs((data->ray.map_y-data->cam.pos_y+(1-data->ray.step_y)/2)/data->ray.rayDir_y);
}

void ray_calc_column(t_data *data)
{
    data->line_height = abs((int)((double)data->screen_heigth/data->ray.wall_dist));

    data->draw_start = -data->line_height/2+(double)data->screen_heigth/2;
    data->draw_end = data->line_height/2+(double)data->screen_heigth/2;

    if (data->draw_start < 0)
        data->draw_start = 0;
    if (data->draw_end >= data->screen_heigth)
        data->draw_end = data->screen_heigth - 1;
}

void ray_calc_tex_pos(t_data *data)
{
    //wall orientation
    if (data->ray.side == 0) 
        data->tex.wall_x = data->ray.rayPos_y + data->ray.wall_dist*data->ray.rayDir_y;
    else
        data->tex.wall_x = data->ray.rayPos_x + data->ray.wall_dist*data->ray.rayDir_x;
    data->tex.wall_x -= floor(data->tex.wall_x);

    data->tex.tex_x = (int)(data->tex.wall_x*data->tex.w);
    if (data->ray.side == 0 && data->ray.rayDir_x > 0)
        data->tex.tex_x = data->tex.w - data->tex.tex_x - 1;
    if (data->ray.side == 1 && data->ray.rayDir_y < 0)
        data->tex.tex_x = data->tex.w - data->tex.tex_x - 1;
}

void raycast_wall(t_data *data)
{   
    ray_init(data);
    ray_find_first_inter(data);
    ray_DDA(data);
    ray_calc_column(data);
    ray_calc_tex_pos(data);

    data->y = data->draw_start;
    while(data->y < data->draw_end) {
        data->tex.tex_y = (int)((data->y * 2 - data->screen_heigth + data->line_height) * (data->tex.h /2)/data->line_height);
        if (data->ray.side == 0 && data->ray.rayDir_x > 0) 
            data->mlx.color = ((unsigned int*)data->tex.tex_tab[0])[(data->tex.w * data->tex.tex_y + data->tex.tex_x)];
        else if (data->ray.side == 0 && data->ray.rayDir_x < 0)
            data->mlx.color = ((unsigned int*)data->tex.tex_tab[1])[(data->tex.w * data->tex.tex_y + data->tex.tex_x)];
        else if (data->ray.side == 1 && data->ray.rayDir_y > 0)
            data->mlx.color = ((unsigned int*)data->tex.tex_tab[2])[(data->tex.w * data->tex.tex_y + data->tex.tex_x)];
        else if (data->ray.side == 1 && data->ray.rayDir_y < 0)
            data->mlx.color = ((unsigned int*)data->tex.tex_tab[3])[(data->tex.w * data->tex.tex_y + data->tex.tex_x)];
        //if (data->ray.side == 1)
        //    data->mlx.color = (data->mlx.color >>1) & 8355711;
        my_mlx_pixel_put(data, data->x, data->y, data->mlx.color);
        data->y++;
    }
}