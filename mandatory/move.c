/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:24:20 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:24:21 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	rotate_cam(t_cam *cam)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = cam->dir_y;
	cam->dir_y = cam->dir_y * cos(-cam->rot_speed)
		- cam->dir_x * sin(-cam->rot_speed);
	cam->dir_x = old_dir_y * sin(-cam->rot_speed)
		+ cam->dir_x * cos(-cam->rot_speed);
	old_plane_y = cam->plane_y;
	cam->plane_y = cam->plane_y * cos(-cam->rot_speed)
		- cam->plane_x * sin(-cam->rot_speed);
	cam->plane_x = old_plane_y * sin(-cam->rot_speed)
		+ cam->plane_x * cos(-cam->rot_speed);
}

void	move_2(t_data *data, t_cam *cam)
{
	if (cam->rotate)
	{
		rotate_cam(cam);
	}
	if (cam->right)
	{
		if (data->map[(int)(cam->pos_y + cam->plane_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + 0.1 + cam->plane_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + cam->plane_y * cam->speed)] [(int)(cam->pos_x + 0.1)] != 49
			&& data->map[(int)(cam->pos_y - 0.1 + cam->plane_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + cam->plane_y * cam->speed)] [(int)(cam->pos_x - 0.1)] != 49)
			cam->pos_y += cam->plane_y * cam->speed;
		if (data->map[(int)cam->pos_y] [(int)(cam->pos_x + cam->plane_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x + 0.1 + cam->plane_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y + 0.1)] [(int)(cam->pos_x + cam->plane_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x - 0.1 + cam->plane_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y - 0.1)] [(int)(cam->pos_x + cam->plane_x * cam->speed)] != 49)
			cam->pos_x += cam->plane_x * cam->speed;
	}
	if (cam->left)
	{
		if (data->map[(int)(cam->pos_y - cam->plane_y * cam->speed)][(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + 0.1 - cam->plane_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y - cam->plane_y * cam->speed)] [(int)(cam->pos_x + 0.1)] != 49
			&& data->map[(int)(cam->pos_y - 0.1 - cam->plane_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y - cam->plane_y * cam->speed)] [(int)(cam->pos_x - 0.1)] != 49)
			cam->pos_y -= cam->plane_y * cam->speed;
		if (data->map[(int)cam->pos_y] [(int)(cam->pos_x - cam->plane_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x + 0.1 - cam->plane_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y + 0.1)] [(int)(cam->pos_x - cam->plane_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x - 0.1 - cam->plane_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y - 0.1)] [(int)(cam->pos_x - cam->plane_x * cam->speed)] != 49)
			cam->pos_x -= cam->plane_x * cam->speed;
	}
}

void	move(t_data *data, t_cam *cam)
{
	if (cam->front)
	{
		if (data->map[(int)(cam->pos_y + cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + 0.1 + cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + cam->dir_y * cam->speed)] [(int)(cam->pos_x + 0.1)] != 49
			&& data->map[(int)(cam->pos_y - 0.1 + cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + cam->dir_y * cam->speed)] [(int)(cam->pos_x - 0.1)] != 49)
			cam->pos_y += cam->dir_y * cam->speed;
		if (data->map[(int)cam->pos_y] [(int)(cam->pos_x + cam->dir_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y + 0.1)] [(int)(cam->pos_x + cam->dir_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x + 0.1 + cam->dir_x * cam->speed)] != 49
			&& data->map[(int)(cam->pos_y - 0.1)] [(int)(cam->pos_x + cam->dir_x * cam->speed)] != 49
			&& data->map[(int)cam->pos_y] [(int)(cam->pos_x - 0.1 + cam->dir_x * cam->speed)] != 49)
			cam->pos_x += cam->dir_x * cam->speed;
	}
	if (cam->back)
	{
		if (data->map[(int)(cam->pos_y - cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y + 0.1 - cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y - cam->dir_y * cam->speed)] [(int)(cam->pos_x + 0.1)] != 49
			&& data->map[(int)(cam->pos_y - 0.1 - cam->dir_y * cam->speed)] [(int)cam->pos_x] != 49
			&& data->map[(int)(cam->pos_y - cam->dir_y * cam->speed)] [(int)(cam->pos_x - 0.1)] != 49)
			cam->pos_y -= cam->dir_y * cam->speed;
		if (data->map[(int)cam->pos_y]
			[(int)(cam->pos_x - cam->dir_x * cam->speed)] != 49)
			cam->pos_x -= cam->dir_x * cam->speed;
	}
	move_2(data, cam);
}
