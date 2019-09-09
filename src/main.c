/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:32:29 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/28 00:26:48 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw(t_fdf *fdf)
{
	!(fdf->ui & 2) ? clear_img(fdf->img) : 0;
	draw_ui(fdf);
	fdf->map->drawcenter =
		set_dpoint(fdf->map->center.x * fdf->cellsize,
					fdf->map->center.y * fdf->cellsize, 0);
	!(fdf->ui & 2) ? draw_map(fdf) : 0;
	fdf->ui &= 1;
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win->win_ptr,
							fdf->img->img_ptr, 0, 0);
	draw_ui(fdf);
}

static void	input_hook(t_fdf **fdf)
{
	mlx_mouse_hook((*fdf)->win->win_ptr, mouseclick, *fdf);
	mlx_hook((*fdf)->win->win_ptr, 17, 1, red_x_button, (void *)0);
	mlx_hook((*fdf)->win->win_ptr, 2, 3, deal_key, *fdf);
}

static void	init_fdf(t_fdf **fdf, int fd, t_flg *flg, char *title)
{
	(*fdf)->map = new_map(fd);
	if (!((*fdf)->mlx_ptr = mlx_init()))
		error("Failed to set up the connection to the X server");
	(*fdf)->win = new_window(fdf, flg->size[0], flg->size[1], title);
	(*fdf)->img = new_image(fdf, set_point(flg->size[0], flg->size[1], 0));
	(*fdf)->cam.coord = set_point((*fdf)->win->x_win / 2,
								(*fdf)->win->y_win / 2, 0);
	(*fdf)->cam.angle = set_dpoint(0, 0, 0);
	(*fdf)->cam.speed = 10;
	(*fdf)->cam.degree = PI / 180 * flg->deg;
	(*fdf)->cellsize = CELLSIZE;
	(*fdf)->map->center = set_dpoint((double)((*fdf)->map->size.x - 1) / 2,
									(double)((*fdf)->map->size.y - 1) / 2,
									((*fdf)->map->max + (*fdf)->map->min) / 2);
	(*fdf)->map->view = new_view((*fdf)->map);
	(*fdf)->map->projection = TRUE_ISO;
	(*fdf)->map->col_mode = 1;
	(*fdf)->ui = 0;
	(*fdf)->map->grad.col_cnt = flg->col_cnt;
	set_grad_colors((*fdf)->map, flg);
	set_custom_color((*fdf)->map);
	switch_projection(fdf);
}

static void	init_flg(t_flg *flg, int ac, char **av)
{
	flg->flag = 0;
	flg->args = 2;
	flg->help = 0;
	flg->col_cnt = 5;
	flg->size[0] = WIN_X;
	flg->size[1] = WIN_Y;
	flg->deg = DEGREE;
	valid_stdin(flg, ac, av);
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_flg	*flg;
	int		fd;

	if (argc == 1)
		usage(argv[0]);
	if (!(flg = (t_flg*)malloc(sizeof(t_flg))))
		error("No memory allocated for FLAGS");
	init_flg(flg, argc, argv);
	if ((fd = open(argv[argc - 1], O_RDONLY)) == -1)
		error("Can't open SOURCE file");
	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
	{
		close(fd);
		error("No memory allocated for FDF");
	}
	init_fdf(&fdf, fd, flg, argv[argc - 1]);
	draw(fdf);
	input_hook(&fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
