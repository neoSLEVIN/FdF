/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 01:06:13 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/10 02:20:35 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	degree(t_flg *flg, int ac, char **av, int i)
{
	size_t	len;

	flg->flag & F_DEG ?
		err_usage("More than 1 degree flag", av[0], flg->help) : 0;
	flg->flag |= F_DEG;
	flg->args += 2;
	i >= ac - 2 ?
		err_usage("Incorrect use of the degree flag\nTry '--degree 3'", av[0],
			flg->help) : 0;
	len = ft_strlen(av[i + 1]);
	if (len < 1 || len > 3)
		err_usage("Incorrect use of the degree flag\nTry '-d 3'", av[0],
			flg->help);
	flg->deg = ft_atoi(av[i + 1]);
	if (flg->deg < 1 || flg->deg > 359 || (flg->deg < 10 && len != 1) ||
		(flg->deg >= 10 && flg->deg < 100 && len != 2))
		err_usage("Range for degree must be in [1...359]", av[0], flg->help);
}

static void	size(t_flg *flg, int ac, char **av, int i)
{
	size_t	len;
	int		j;

	flg->flag & F_SIZ ?
		err_usage("More than 1 size flag", av[0], flg->help) : 0;
	flg->flag |= F_SIZ;
	flg->args += 3;
	i >= ac - 3 ?
		err_usage("Incorrect use of the size flag\nTry '--size 1000 1000'",
			av[0], flg->help) : 0;
	j = -1;
	while (++j < 2)
	{
		len = ft_strlen(av[i + 1 + j]);
		if (len < 3 || len > 4)
			err_usage("Incorrect use of the size flag\nTry '-s 1000 1000'",
				av[0], flg->help);
		flg->size[j] = ft_atoi(av[i + 1 + j]);
		if (flg->size[j] < 300 || flg->size[j] > 1700 ||
			(flg->size[j] < 1000 && len != 3))
			err_usage("Range for size must be in [300...1700]", av[0],
				flg->help);
	}
}

static void	gradient(t_flg *flg, int ac, char **av, int i)
{
	size_t	len;
	int		j;

	flg->flag & F_GRD ?
		err_usage("More than 1 gradient flag", av[0], flg->help) : 0;
	flg->flag |= F_GRD;
	flg->args += 4;
	i >= ac - 4 ?
		err_usage("Incorrect use of the gradient flag\nTry '-g 25 50 75'",
			av[0], flg->help) : 0;
	j = -1;
	while (++j < 3)
	{
		len = ft_strlen(av[i + 1 + j]);
		if (len < 1 || len > 3)
			err_usage("Incorrect use of the gradient flag", av[0], flg->help);
		flg->grad[j] = ft_atoi(av[i + 1 + j]);
		if (flg->grad[j] < 1 || flg->grad[j] > 99 ||
			(flg->grad[j] < 10 && len != 1) || (flg->grad[j] > 9 && len != 2))
			err_usage("Range for gradient must be in [1...99]", av[0],
				flg->help);
		if (j != 0 && flg->grad[j] <= flg->grad[j - 1])
			err_usage("Gradient arguments should be in ascending order", av[0],
				flg->help);
	}
}

static void	color(t_flg *flg, int ac, char **av, int i)
{
	size_t	len;
	int		j;

	flg->flag & F_COL ?
		err_usage("More than 1 color flag", av[0], flg->help) : 0;
	flg->flag |= F_COL;
	flg->args += 6;
	i >= ac - 6 ?
		err_usage("Incorrect use of the color flag", av[0], flg->help) : 0;
	j = -1;
	while (++j < 5)
	{
		len = ft_strlen(av[i + 1 + j]);
		if (!(len == 3 || len == 5 || len == 8) || av[i + 1 + j][0] != '0' ||
			av[i + 1 + j][1] != 'x')
			err_usage("Incorrect use of the color flag", av[0], flg->help);
		if (!is_hex(&av[i + 1 + j][2]))
			err_usage("Incorrect hex color\nExample: 0xf or 0xf7d", av[0],
				flg->help);
		hex_to_rgb(&av[i + 1 + j][2], &flg->col[j]);
	}
}

void		valid_stdin(t_flg *flg, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		!ft_strcmp(av[i], "--help") ? ++flg->args : 0;
		!ft_strcmp(av[i], "--help") ? flg->help = 1 : 0;
	}
	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "--color") || !ft_strcmp(av[i], "-c"))
			color(flg, ac, av, i);
		else if (!ft_strcmp(av[i], "--degree") || !ft_strcmp(av[i], "-d"))
			degree(flg, ac, av, i);
		else if (!ft_strcmp(av[i], "--gradient") || !ft_strcmp(av[i], "-g"))
			gradient(flg, ac, av, i);
		else if (!ft_strcmp(av[i], "--size") || !ft_strcmp(av[i], "-s"))
			size(flg, ac, av, i);
		else if (!ft_strcmp(av[i], "--col-grad") || !ft_strcmp(av[i], "-X"))
			col_grad(flg, ac, av, i);
	}
	if (ac != flg->args || flg->help)
		err_usage((ac == flg->args || (ac == 2 && flg->help) ? NULL :
			"Wrong arguments/source in program call"), av[0], flg->help);
}
