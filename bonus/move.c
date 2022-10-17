/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:27:22 by fmustin           #+#    #+#             */
/*   Updated: 2022/10/12 12:27:23 by fmustin          ###   ########.fr       */
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

void	move_4(t_data *d, t_cam *c)
{
	double	tmp_y;
	double	tmp_x;

	tmp_y = c->pos_y - (c->plane_y * c->sp);
	tmp_x = c->pos_x - (c->plane_x * c->sp);
	if (c->left)
	{
		if (d->map[(int)(tmp_y)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y + 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x + 0.1)] != 49
			&& d->map[(int)(tmp_y - 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x - 0.1)] != 49)
			c->pos_y -= c->plane_y * c->sp;
		if (d->map[(int)c->pos_y][(int)(tmp_x)] != 49
			&& d->map[(int)(c->pos_y + 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x + 0.1)] != 49
			&& d->map[(int)(c->pos_y - 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x - 0.1)] != 49)
			c->pos_x -= c->plane_x * c->sp;
	}
}

void	move_3(t_data *d, t_cam *c)
{
	double	tmp_y;
	double	tmp_x;

	tmp_y = c->pos_y + (c->plane_y * c->sp);
	tmp_x = c->pos_x + (c->plane_x * c->sp);
	if (c->rotate)
	{
		rotate_cam(c);
	}
	if (c->right)
	{
		if (d->map[(int)(tmp_y)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y + 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x + 0.1)] != 49
			&& d->map[(int)(tmp_y - 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x - 0.1)] != 49)
			c->pos_y += c->plane_y * c->sp;
		if (d->map[(int)c->pos_y][(int)(tmp_x)] != 49
			&& d->map[(int)(c->pos_y + 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x + 0.1)] != 49
			&& d->map[(int)(c->pos_y - 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x - 0.1)] != 49)
			c->pos_x += c->plane_x * c->sp;
	}
	move_4(d, c);
}

void	move_2(t_data *d, t_cam *c)
{
	double	tmp_y;
	double	tmp_x;

	tmp_y = c->pos_y - (c->dir_y * c->sp);
	tmp_x = c->pos_x - (c->dir_x * c->sp);
	if (c->back)
	{
		if (d->map[(int)(tmp_y)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y + 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x + 0.1)] != 49
			&& d->map[(int)(tmp_y - 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x - 0.1)] != 49)
			c->pos_y -= c->dir_y * c->sp;
		if (d->map[(int)c->pos_y][(int)(tmp_x)] != 49
			&& d->map[(int)(c->pos_y + 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x + 0.1)] != 49
			&& d->map[(int)(c->pos_y - 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x - 0.1)] != 49)
			c->pos_x -= c->dir_x * c->sp;
	}
	move_3(d, c);
}

void	move(t_data *d, t_cam *c)
{
	double	tmp_y;
	double	tmp_x;

	tmp_y = c->pos_y + (c->dir_y * c->sp);
	tmp_x = c->pos_x + (c->dir_x * c->sp);
	if (c->front)
	{
		if (d->map[(int)(tmp_y)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y + 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x + 0.1)] != 49
			&& d->map[(int)(tmp_y - 0.1)][(int)c->pos_x] != 49
			&& d->map[(int)(tmp_y)][(int)(c->pos_x - 0.1)] != 49)
			c->pos_y += c->dir_y * c->sp;
		if (d->map[(int)c->pos_y][(int)(tmp_x)] != 49
			&& d->map[(int)(c->pos_y + 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x + 0.1)] != 49
			&& d->map[(int)(c->pos_y - 0.1)][(int)(tmp_x)] != 49
			&& d->map[(int)c->pos_y][(int)(tmp_x - 0.1)] != 49)
			c->pos_x += c->dir_x * c->sp;
	}
	move_2(d, c);
}
