/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:19:55 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/27 23:49:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_rgb	draw_pxl(t_fdf *fdf, t_mappoint p1, t_mappoint p2, double t)
{
	t_rgb	color;
	t_rgb	*start;
	t_rgb	*end;

	start = p1.view_color;
	end = p2.view_color;
	if (p1.z == p2.z && p1.view_color->blue == p2.view_color->blue &&
		p1.view_color->green == p2.view_color->green &&
		p1.view_color->red == p2.view_color->red)
		t = 0;
	if (fdf->map->col_mode == 0)
		return (get_grad_color(fdf->map, p1.z + t * (p2.z - p1.z)));
	else if (start != NULL && end != NULL)
	{
		color.red = start->red + t * (end->red - start->red);
		color.green = start->green + t * (end->green - start->green);
		color.blue = start->blue + t * (end->blue - start->blue);
		return (color);
	}
	return (set_rgb(255, 255, 255));
}

static void		draw_dx(t_fdf *fdf, t_mappoint start, t_mappoint end)
{
	t_point		delta;
	t_point		xyd;
	t_dpoint	coord;

	delta = set_point(fabs(start.coord.x - end.coord.x),
		fabs(start.coord.y - end.coord.y), 0);
	xyd.y = end.coord.y - start.coord.y;
	xyd.y > 0 ? xyd.y = 1 : 0;
	xyd.y < 0 ? xyd.y = -1 : 0;
	coord = start.coord;
	coord.z = (double)delta.x / 2;
	xyd.x = -1;
	!delta.x ? delta.x = 1 : 0;
	while (++xyd.x < end.coord.x - start.coord.x)
	{
		plot(fdf->img,
			draw_pxl(fdf, start, end, (double)xyd.x / delta.x),
			set_point(coord.x + xyd.x, coord.y, 0));
		coord.z -= delta.y;
		if (coord.z < 0)
		{
			coord.y += xyd.y;
			coord.z += delta.x;
		}
	}
}

static void		draw_dy(t_fdf *fdf, t_mappoint start, t_mappoint end)
{
	t_point		delta;
	t_point		xyd;
	t_dpoint	coord;

	delta = set_point(fabs(start.coord.x - end.coord.x),
		fabs(start.coord.y - end.coord.y), 0);
	xyd.x = end.coord.x - start.coord.x;
	xyd.x > 0 ? xyd.x = 1 : 0;
	xyd.x < 0 ? xyd.x = -1 : 0;
	coord = start.coord;
	coord.z = (double)delta.y / 2;
	xyd.y = -1;
	!delta.y ? delta.y = 1 : 0;
	while (++xyd.y < end.coord.y - start.coord.y)
	{
		plot(fdf->img,
			draw_pxl(fdf, start, end, (double)xyd.y / delta.y),
			set_point(coord.x, coord.y + xyd.y, 0));
		coord.z -= delta.x;
		if (coord.z < 0)
		{
			coord.x += xyd.x;
			coord.z += delta.y;
		}
	}
}

void			draw_line(t_fdf *fdf, t_mappoint start, t_mappoint end)
{
	if (fabs(end.coord.y - start.coord.y) < fabs(end.coord.x - start.coord.x))
		(start.coord.x > end.coord.x) ?
			draw_dx(fdf, end, start) : draw_dx(fdf, start, end);
	else
		(start.coord.y > end.coord.y) ?
			draw_dy(fdf, end, start) : draw_dy(fdf, start, end);
}
