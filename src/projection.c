/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:52:35 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/27 22:37:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	copy_map_to_view(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			map->view[y][x] = map->map[y][x];
	}
}

static void	iso(t_map *map)
{
	t_point		xy;
	t_dpoint	prev;
	t_dpoint	cs;

	cs.x = map->projection == TRUE_ISO ?
		cos(PI / 180 * 30) : cos(PI / 180 * 26.57);
	cs.y = map->projection == TRUE_ISO ?
		sin(PI / 180 * 30) : sin(PI / 180 * 26.57);
	xy.y = -1;
	while (++xy.y < map->size.y)
	{
		xy.x = -1;
		while (++xy.x < map->size.x)
		{
			prev.x = map->view[xy.y][xy.x].coord.x - map->center.x;
			prev.y = map->view[xy.y][xy.x].coord.y - map->center.y;
			prev.z = map->view[xy.y][xy.x].coord.z - map->center.z;
			map->view[xy.y][xy.x].coord.x = (prev.x - prev.y) * cs.x +
				map->center.x;
			map->view[xy.y][xy.x].coord.y = (prev.x + prev.y) * cs.y +
				map->center.y - prev.z;
		}
	}
}

static void	free_look(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map->size.y)
	{
		x = -1;
		while (++x < fdf->map->size.x)
		{
			rotate_x(&fdf->map->view[y][x].coord, &fdf->map->center,
				PI / 180 * 45);
			rotate_y(&fdf->map->view[y][x].coord, &fdf->map->center,
				PI / 180 * -42);
			rotate_z(&fdf->map->view[y][x].coord, &fdf->map->center,
				PI / 180 * 30);
			rotate_y(&fdf->map->view[y][x].coord, &fdf->map->center,
				PI / 180 * 6);
		}
	}
}

void		switch_projection(t_fdf **fdf)
{
	copy_map_to_view((*fdf)->map);
	(*fdf)->map->col_mode ^= 1;
	switch_color((*fdf)->map);
	(*fdf)->map->projection += 1;
	if ((*fdf)->map->projection > 2)
	{
		(*fdf)->map->projection = 0;
		free_look(*fdf);
	}
	if ((*fdf)->map->projection != FREE)
		iso((*fdf)->map);
}
