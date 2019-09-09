/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:15:42 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/04 21:45:43 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	err_usage(char *err_msg, char *app_name, _Bool full)
{
	if (err_msg)
	{
		ft_putstr("Error: ");
		ft_putendl(err_msg);
	}
	return (full ? usage(app_name) : lite_usage(app_name));
}

int	diff_size_err(int line)
{
	ft_putstr("Error: Different size between ");
	ft_putnbr(line);
	ft_putstr(" and ");
	ft_putnbr(line + 1);
	ft_putendl(" lines");
	exit(ERR_EXIT);
}

int	empty_line_err(int line)
{
	ft_putstr("Error: Empty ");
	ft_putnbr(line + 1);
	ft_putendl(" line");
	exit(ERR_EXIT);
}

int	wrong_line_err(int line, int word, int type)
{
	ft_putstr("Error: Wrong ");
	type == INT ? ft_putstr("value(not integer) of ") : 0;
	type == COLOR ? ft_putstr("color of ") : 0;
	ft_putstr("point in ");
	ft_putnbr(line + 1);
	ft_putstr(" line at ");
	ft_putnbr(word + 1);
	ft_putendl(" position");
	exit(ERR_EXIT);
}

int	error(char *err_msg)
{
	if (err_msg)
	{
		ft_putstr("Error: ");
		ft_putendl(err_msg);
	}
	exit(ERR_EXIT);
}
