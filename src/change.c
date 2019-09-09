/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 03:42:41 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/27 21:25:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_grad_colors(t_map *map, t_flg *flg)
{
	int	i;

	hex_to_rgb("257cba", &map->grad.col[0]);
	hex_to_rgb("2f7218", &map->grad.col[1]);
	hex_to_rgb("66410e", &map->grad.col[2]);
	hex_to_rgb("888", &map->grad.col[3]);
	hex_to_rgb("f", &map->grad.col[4]);
	map->grad.range[0] = 0;
	map->grad.range[1] = 0.25;
	map->grad.range[2] = 0.50;
	map->grad.range[3] = 0.75;
	i = -1;
	if (flg->flag & F_COL)
		while (++i < flg->col_cnt)
		{
			map->grad.col[i].red = flg->col[i].red;
			map->grad.col[i].green = flg->col[i].green;
			map->grad.col[i].blue = flg->col[i].blue;
		}
	i = -1;
	if (flg->flag & F_GRD)
		while (++i < flg->col_cnt - 2)
			map->grad.range[i + 1] = (double)flg->grad[i] / 100;
	map->grad.range[flg->col_cnt - 1] = 1;
}

static void	valid_col_grad(t_flg *flg, char *arg, char *app_name, int type)
{
	size_t	len;

	len = ft_strlen(arg);
	if (type == COLOR)
	{
		if (len != 1 && len != 3 && len != 6)
			err_usage("Incorrect use of the color argument of the -X flag",
				app_name, flg->help);
		if (!is_hex(arg))
			err_usage("Incorrect hex color\nExample: 0xf or 0xf7d or 0xabcdef",
				app_name, flg->help);
	}
	else
	{
		if (len < 1 || len > 2)
			err_usage("Incorrect use of the gradient argument of the -X flag",
				app_name, flg->help);
		if (arg[0] < '1' || arg[0] > '9' || (len == 2 && !ft_isdigit(arg[1])))
			err_usage("Range for gradient argument must be in [1...99]",
				app_name, flg->help);
	}
}

static void	col_grad2(t_flg *flg, char **av, int i, int j)
{
	int	col;
	int	grd;

	col = -1;
	grd = -1;
	while (++j < flg->col_cnt * 2 - 2)
	{
		if (!ft_strncmp(av[i + j], "0x", 2) && ++col < flg->col_cnt)
		{
			valid_col_grad(flg, &av[i + j][2], av[0], COLOR);
			hex_to_rgb(&av[i + j][2], &flg->col[col]);
		}
		else if (++grd < flg->col_cnt - 2)
		{
			valid_col_grad(flg, av[i + j], av[0], INT);
			flg->grad[grd] = ft_atoi(av[i + j]);
			if (grd != 0 && flg->grad[grd] <= flg->grad[grd - 1])
				err_usage("Gradient arguments should be in ascending order",
					av[0], flg->help);
		}
		else
			err_usage("Wrong count of arguments for the -X flag",
				av[0], flg->help);
	}
}

void		col_grad(t_flg *flg, int ac, char **av, int i)
{
	size_t	len;

	flg->flag & F_COL ?
		err_usage("More than 1 color flag", av[0], flg->help) : 0;
	flg->flag & F_GRD ?
		err_usage("More than 1 gradient flag", av[0], flg->help) : 0;
	flg->flag |= F_COL + F_GRD;
	len = (i < ac - 1) ? ft_strlen(av[i + 1]) : 0;
	!len ? err_usage("Incorrect use of the -X flag", av[0], flg->help) : 0;
	if (len > 2 || av[i + 1][0] < '1' || av[i + 1][0] > '9' ||
		(len == 2 && !ft_isdigit(av[i + 1][1])))
		err_usage("Incorrect main argument for the -X flag", av[0], flg->help);
	flg->col_cnt = ft_atoi(av[i + 1]);
	if (flg->col_cnt < 2 || flg->col_cnt > 11)
		err_usage("Range for main argument of -X flag must be in [2...11]",
			av[0], flg->help);
	flg->args += 2 * flg->col_cnt;
	(i >= ac - (2 * flg->col_cnt)) ?
		err_usage("Incorrect use of the -X flag", av[0], flg->help) : 0;
	col_grad2(flg, av, i + 2, -1);
}
