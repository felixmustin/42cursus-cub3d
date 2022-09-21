#include "main.h"

int check_move(t_data *data, int y, int x)
{
    int i;
    i = 0;
    while (i < data->numSprite)
    {
        if (x == (int)data->sprite[i].x && y == (int)data->sprite[i].y)
            if (!data->sprite[i].walkable)
                return (0);
        i++;
    }
    return (1);
}

void rotate_cam(t_cam *cam)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = cam->dir_x;
    cam->dir_x = cam->dir_x*cos(-cam->rot_speed) - cam->dir_y*sin(-cam->rot_speed);
    cam->dir_y = old_dir_x*sin(-cam->rot_speed) + cam->dir_y*cos(-cam->rot_speed);
    old_plane_x = cam->plane_x;
    cam->plane_x = cam->plane_x * cos(-cam->rot_speed) - cam->plane_y*sin(-cam->rot_speed);
    cam->plane_y = old_plane_x*sin(-cam->rot_speed) + cam->plane_y*cos(-cam->rot_speed);
}

void move_2(t_data *data, t_cam *cam)
{
    if (cam->rotate) {
        rotate_cam(cam);
    }
    if (cam->right) {
        if (!check_move(data, (int)(cam->pos_y + cam->plane_y * cam->speed), (int)(cam->pos_x + cam->plane_x * cam->speed)))
            return ;
        if (data->map[(int)(cam->pos_y + cam->plane_y * cam->speed)][(int)cam->pos_x] == 48)
            cam->pos_y += cam->plane_y * cam->speed;
        if (data->map[(int)cam->pos_y][(int)(cam->pos_x + cam->plane_x * cam->speed)] == 48)
            cam->pos_x += cam->plane_x * cam->speed;
    }
    if (cam->left) {
        if (!check_move(data, (int)(cam->pos_y - cam->plane_y * cam->speed), (int)(cam->pos_x - cam->plane_x * cam->speed)))
            return ;
        if (data->map[(int)(cam->pos_y - cam->plane_y * cam->speed)][(int)cam->pos_x] == 48)
            cam->pos_y -= cam->plane_y * cam->speed;
        if (data->map[(int)cam->pos_y][(int)(cam->pos_x - cam->plane_x * cam->speed)] == 48)
            cam->pos_x -= cam->plane_x * cam->speed;
    }
}

void move(t_data *data, t_cam *cam)
{

    if (cam->front) {
        if (!check_move(data, (int)(cam->pos_y + cam->dir_y * cam->speed), (int)(cam->pos_x + cam->dir_x * cam->speed)))
            return ;
        if (data->map[(int)(cam->pos_y + cam->dir_y * cam->speed)][(int)cam->pos_x] == 48)
            cam->pos_y += cam->dir_y * cam->speed;
        if (data->map[(int)cam->pos_y][(int)(cam->pos_x + cam->dir_x * cam->speed)] == 48)
            cam->pos_x += cam->dir_x * cam->speed;
    }
    if (cam->back) {
        if (!check_move(data, (int)(cam->pos_y - cam->dir_y * cam->speed), (int)(cam->pos_x - cam->dir_x * cam->speed)))
            return ;
        if (data->map[(int)(cam->pos_y - cam->dir_y * cam->speed)][(int)cam->pos_x] == 48)
            cam->pos_y -= cam->dir_y * cam->speed;
        if (data->map[(int)cam->pos_y][(int)(cam->pos_x - cam->dir_x * cam->speed)] == 48)
            cam->pos_x -= cam->dir_x * cam->speed;
    }
    move_2(data, cam);
}