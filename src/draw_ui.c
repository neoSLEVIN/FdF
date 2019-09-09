/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:02:20 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/10 02:18:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_ui3(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 125 + LM, 0x00cccccc,
		"Numpad:");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 10, 145 + LM, 0x00cccccc,
		"Fast move: 2, 4, 6, 8, 5");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 10, 165 + LM, 0x00cccccc,
		"Fast zoom: *, /, 0");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 10, 185 + LM, 0x00cccccc,
		"Projection: 1");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 10, 205 + LM, 0x00cccccc,
		"Color: .");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 10, 225 + LM, 0x00cccccc,
		"Map: Enter");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 245 + LM, 0x000047b4,
				   "Exit: Esc");
	mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 265 + LM, 0x00ff3144,
		"Less: Tab");
}

static void	draw_ui2(t_fdf *fdf)
{
	if (fdf->map->projection == FREE)
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr,
			fdf->img->size.x - PROJ1, fdf->img->size.y - 25 + LM, 0x0031cb44,
			"FREE");
	else if (fdf->map->projection == TRUE_ISO)
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr,
			fdf->img->size.x - PROJ2, fdf->img->size.y - 25 + LM, 0x00ff3144,
			"TRUE ISO");
	else if (fdf->map->projection == TWO_ONE_ISO)
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr,
			fdf->img->size.x - PROJ3, fdf->img->size.y - 25 + LM, 0x000047b4,
			"2:1 ISO");
}

void		draw_ui(t_fdf *fdf)
{
	draw_ui2(fdf);
	if (!(fdf->ui & 1))
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 5 + LM, 0x0031cb44,
			"More: Tab");
	else
	{
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 5 + LM, 0x00cccccc,
			"Rotate: W, A, S, D, Q, E");
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 25 + LM, 0x00cccccc,
			"Zoom: Mousewheel, +, -, Z");
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 45 + LM, 0x00cccccc,
			"Move: Arrows, X");
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 65 + LM, 0x00cccccc,
			"Projection: P");
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 85 + LM, 0x00cccccc,
			"Color: C");
		mlx_string_put(fdf->mlx_ptr, fdf->win->win_ptr, 5, 105 + LM, 0x00cccccc,
			"Map: M");
		draw_ui3(fdf);
	}
}
