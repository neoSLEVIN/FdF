/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 01:48:12 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/10 02:21:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	usage3(char *app_name)
{
	ft_putstr("Options can be written out of order, but arguments must ");
	ft_putendl("follow their options.");
	ft_putendl("SOURCE should be the last parameter.\n");
	ft_putstr("Try: ");
	ft_putstr(app_name);
	ft_putendl(" -c 0xf88 0xff8 0x8ff 0xf8f 0xf88 SOURCE");
	ft_putstr(" or: ");
	ft_putstr(app_name);
	ft_putendl(" -c 0x8a4a4a 0x8a8a4a 0x4a8a8a 0x8a4a8a 0x8a4a4a SOURCE");
	ft_putstr(" or: ");
	ft_putstr(app_name);
	ft_putstr(" -X 6  0xf00  33 0xf00  34 0x00f  66 0x00f  67 0xfff  0xfff ");
	ft_putendl("SOURCE");
}

static void	usage2(char *app_name)
{
	ft_putstr("  -X, --col-grad\tChange the custom colors and the values of ");
	ft_putendl("the gradient.");
	ft_putendl("\t\t\tMAIN ARG(1): integer in range [2...11] inclusive. Must");
	ft_putendl("\t\t\t  be first among the arguments of -X flag.");
	ft_putstr("\t\t\tSIDE ARGS(X): list of HEX colors that starts with 0x and");
	ft_putendl("\n\t\t\t  integers in range [1...99] inclusive in ascending");
	ft_putendl("\t\t\t  order. X is the sum of the color and gradient");
	ft_putendl("\t\t\t  arguments reduced by 2. This means that COUNT of");
	ft_putendl("\t\t\t  color's arguments is equal to value of the main");
	ft_putendl("\t\t\t  argument, COUNT of gradient's arguments is equal to");
	ft_putendl("\t\t\t  value of the main argument minus two.");
	ft_putendl("\t\t\tHint: Colors and gradient values can be intertwined.");
	ft_putendl("\t\t\tExample: --col-grad 5  0x257cba  25 0x2F7218");
	ft_putendl("\t\t\t  50 0x66410e  75 0x888  0xf\n");
	ft_putendl("      --help\t\tDisplay this help and exit.\n");
	ft_putstr("In the examples shown standard values that are set without ");
	ft_putendl("options.\n");
	ft_putstr("Gradient values are set for colors from 0(first color) to ");
	ft_putstr("100(last color) in\nascending order. For simplicity, the ");
	ft_putendl("first and last values do not need to be");
	ft_putendl("entered in the options.\n");
	ft_putendl("-X flag is both color and gradient flag at the same time.\n");
	usage3(app_name);
}

int			usage(char *app_name)
{
	ft_putstr("Usage: ");
	ft_putstr(app_name);
	ft_putendl(" [OPTION ARGS]... SOURCE\n");
	ft_putendl("Arguments to options are mandatory.");
	ft_putendl("  -c, --color\t\tChange the custom colors.");
	ft_putendl("\t\t\tARGS(5): HEX colors that starts with 0x.");
	ft_putendl("\t\t\tHint: 0x7 is same as 0x777 and same as 0x777777");
	ft_putendl("\t\t\tExample: --color 0x257cba 0x2F7218 0x66410e 0x888 0xf\n");
	ft_putstr("  -d, --degree\t\t");
	ft_putendl("Change the degree of angle of one turn of the map.");
	ft_putendl("\t\t\tARGS(1): integer in range [1...359] inclusive.");
	ft_putendl("\t\t\tExample: --degree 3\n");
	ft_putendl("  -g, --gradient\tChange the values of the gradient.");
	ft_putendl("\t\t\tARGS(3): integers in range [1...99] inclusive in");
	ft_putendl("\t\t\t  ascending order.");
	ft_putendl("\t\t\tExample: --gradient 25 50 75\n");
	ft_putendl("  -s, --size\t\tResize the window.");
	ft_putendl("\t\t\tARGS(2): integers in range [300...1700] inclusive, the");
	ft_putstr("\t\t\t  first argument is for width, ");
	ft_putendl("the second is for height.");
	ft_putendl("\t\t\tExample: --size 1000 1000\n");
	usage2(app_name);
	exit(1);
}

int			lite_usage(char *app_name)
{
	ft_putstr("Try '");
	ft_putstr(app_name);
	ft_putendl(" --help' for more information.");
	exit(1);
}
