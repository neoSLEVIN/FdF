/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:44:45 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/24 16:13:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mappoint	point_position(t_mappoint point, t_fdf *fdf)
{
	point.coord.x *= fdf->cellsize;
	point.coord.y *= fdf->cellsize;
	point.coord.z *= fdf->cellsize;
	point.coord.x += fdf->cam.coord.x - fdf->map->drawcenter.x;
	point.coord.y += fdf->cam.coord.y - fdf->map->drawcenter.y;
	return (point);
}

void				draw_map(t_fdf *fdf)
{
	t_point		p;
	t_mappoint	start;
	t_mappoint	end;

	p.y = -1;
	while (++p.y < fdf->map->size.y)
	{
		p.x = -1;
		while (++p.x < fdf->map->size.x)
		{
			start = point_position(fdf->map->view[p.y][p.x], fdf);
			plot(fdf->img, *start.view_color,
				set_point(start.coord.x, start.coord.y, start.coord.z));
			if (p.x + 1 < fdf->map->size.x)
			{
				end = point_position(fdf->map->view[p.y][p.x + 1], fdf);
				draw_line(fdf, start, end);
			}
			if (p.y + 1 < fdf->map->size.y)
			{
				end = point_position(fdf->map->view[p.y + 1][p.x], fdf);
				draw_line(fdf, start, end);
			}
		}
	}
}
