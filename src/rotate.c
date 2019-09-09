/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 02:25:47 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/24 23:43:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_dpoint *point, t_dpoint *center, double angle)
{
	t_dpoint	temp;

	temp = set_dpoint(0, point->y - center->y, point->z - center->z);
	point->y = temp.y * cos(angle) - temp.z * sin(angle) + center->y;
	point->z = temp.y * sin(angle) + temp.z * cos(angle) + center->z;
}

void	rotate_y(t_dpoint *point, t_dpoint *center, double angle)
{
	t_dpoint	temp;

	temp = set_dpoint(point->x - center->x, 0, point->z - center->z);
	point->x = temp.x * cos(angle) + temp.z * sin(angle) + center->x;
	point->z = -temp.x * sin(angle) + temp.z * cos(angle) + center->z;
}

void	rotate_z(t_dpoint *point, t_dpoint *center, double angle)
{
	t_dpoint	temp;

	temp = set_dpoint(point->x - center->x, point->y - center->y, 0);
	point->x = temp.x * cos(angle) - temp.y * sin(angle) + center->x;
	point->y = temp.x * sin(angle) + temp.y * cos(angle) + center->y;
}

void	rotate_fdf(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map->size.y)
	{
		x = -1;
		while (++x < fdf->map->size.x)
		{
			if (fdf->cam.angle.x != 0)
				rotate_x(&fdf->map->view[y][x].coord, &fdf->map->center,
					fdf->cam.angle.x);
			else if (fdf->cam.angle.y != 0)
				rotate_y(&fdf->map->view[y][x].coord, &fdf->map->center,
					fdf->cam.angle.y);
			else if (fdf->cam.angle.z != 0)
				rotate_z(&fdf->map->view[y][x].coord, &fdf->map->center,
					fdf->cam.angle.z);
		}
	}
}
