/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 23:07:16 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/06 23:07:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_point		set_point(int x, int y, int z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_dpoint	set_dpoint(double x, double y, double z)
{
	t_dpoint	dpoint;

	dpoint.x = x;
	dpoint.y = y;
	dpoint.z = z;
	return (dpoint);
}

t_rgb		set_rgb(int red, int green, int blue)
{
	t_rgb	color;

	color.red = red;
	color.green = green;
	color.blue = blue;
	return (color);
}
