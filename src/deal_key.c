/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 01:44:51 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/04 20:34:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_camera(t_fdf *fdf, int key)
{
	if (key == W_KEY)
		fdf->cam.angle.x += fdf->cam.degree;
	else if (key == S_KEY)
		fdf->cam.angle.x -= fdf->cam.degree;
	else if (key == D_KEY)
		fdf->cam.angle.y += fdf->cam.degree;
	else if (key == A_KEY)
		fdf->cam.angle.y -= fdf->cam.degree;
	else if (key == Q_KEY)
		fdf->cam.angle.z -= fdf->cam.degree;
	else if (key == E_KEY)
		fdf->cam.angle.z += fdf->cam.degree;
	rotate_fdf(fdf);
	fdf->cam.angle = set_dpoint(0, 0, 0);
}

static void	move_camera(t_fdf *fdf, int key)
{
	if (key == LEFT || key == FOUR_NUM)
		fdf->cam.coord.x += fdf->cam.speed * ((key == LEFT) ? 1 : 10);
	if (key == RIGHT || key == SIX_NUM)
		fdf->cam.coord.x -= fdf->cam.speed * ((key == RIGHT) ? 1 : 10);
	if (key == UP || key == EIGHT_NUM)
		fdf->cam.coord.y += fdf->cam.speed * ((key == UP) ? 1 : 10);
	if (key == DOWN || key == TWO_NUM)
		fdf->cam.coord.y -= fdf->cam.speed * ((key == DOWN) ? 1 : 10);
}

static void	zoom_camera(t_fdf *fdf, int key)
{
	if (key == MINUS || key == PLUS)
		key == MINUS ? --fdf->cellsize : ++fdf->cellsize;
	else
		fdf->cellsize += (key == DIV) ? -10 : 10;
	fdf->cellsize < 1 ? fdf->cellsize = 1 : 0;
}

static void	map_camera(t_fdf *fdf)
{
	fdf->map->projection = -1;
	switch_projection(&fdf);
}

int			deal_key(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	if (key == ESC)
		red_x_button(0);
	if (fdf->map->projection == FREE && is_rotate(key))
		rotate_camera(fdf, key);
	if (is_move(key))
		move_camera(fdf, key);
	if (key == MINUS || key == PLUS || key == DIV || key == MULT)
		zoom_camera(fdf, key);
	if (key == M_KEY || key == ENTER || key == ENTER_NUM)
		map_camera(fdf);
	if (key == Z_KEY || key == ZERO_NUM)
		fdf->cellsize = CELLSIZE;
	if (key == X_KEY || key == FIVE_NUM)
		fdf->cam.coord = set_point(fdf->win->x_win / 2, fdf->win->y_win / 2, 0);
	if (key == TAB)
		fdf->ui ^= 3;
	if (key == C_KEY || key == DOT)
		switch_color(fdf->map);
	if (key == P_KEY || key == ONE_NUM)
		switch_projection(&fdf);
	draw(fdf);
	return (0);
}
