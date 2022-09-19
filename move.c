#include "main.h"

int check_move(t_data *data, int y, int x)
{
    int i;
    i = 0;
    while (i < data->numSprite)
    {
        if (x == (int)data->sprite[i].x && y == (int)data->sprite[i].y)
            return (0);
        i++;
    }
    if (data->map[y][x] == 48)
        return (1);
    return (0);
}

void move_2(t_data *data, t_cam *cam)
{
    double old_dir_x;
    double old_plane_x;

    if (cam->rotate) {
        old_dir_x = cam->dir_x;
        cam->dir_x = cam->dir_x*cos(-cam->rot_speed) - cam->dir_y*sin(-cam->rot_speed);
        cam->dir_y = old_dir_x*sin(-cam->rot_speed) + cam->dir_y*cos(-cam->rot_speed);
        old_plane_x = cam->plane_x;
        cam->plane_x = cam->plane_x * cos(-cam->rot_speed) - cam->plane_y*sin(-cam->rot_speed);
        cam->plane_y = old_plane_x*sin(-cam->rot_speed) + cam->plane_y*cos(-cam->rot_speed);
    }
    if (cam->right) {
        if (data->map[(int)(cam->pos_x + cam->plane_x * cam->speed)][(int)cam->pos_y] == 48)
            cam->pos_x += cam->plane_x * cam->speed;
        if (data->map[(int)cam->pos_x][(int)(cam->pos_y + cam->plane_y * cam->speed)] == 48)
            cam->pos_y += cam->plane_y * cam->speed;
    }
    if (cam->left) {
        if (data->map[(int)(cam->pos_x - cam->plane_x * cam->speed)][(int)cam->pos_y] == 48)
            cam->pos_x -= cam->plane_x * cam->speed;
        if (data->map[(int)cam->pos_x][(int)(cam->pos_y - cam->plane_y * cam->speed)] == 48)
            cam->pos_y -= cam->plane_y * cam->speed;
    }
}

void move(t_data *data, t_cam *cam)
{

    if (cam->front) {
        if (check_move(data, (int)(cam->pos_y + cam->dir_y * cam->speed), (int)cam->pos_x))
            cam->pos_y += cam->dir_y * cam->speed;
        if (check_move(data, (int)cam->pos_y, (int)(cam->pos_x + cam->dir_x * cam->speed)))
            cam->pos_x += cam->dir_x * cam->speed;
    }
    if (cam->back) {
        if (check_move(data, (int)(cam->pos_y - cam->dir_y * cam->speed), (int)cam->pos_x))
            cam->pos_y -= cam->dir_y * cam->speed;
        if (check_move(data, (int)cam->pos_y, (int)(cam->pos_x - cam->dir_x * cam->speed)))
            cam->pos_x -= cam->dir_x * cam->speed;
    }
    move_2(data, cam);
}