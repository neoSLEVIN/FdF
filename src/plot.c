/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:22:40 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/14 17:23:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot(t_img *img, t_rgb color, t_point coord)
{
	int	*i;

	i = (int *)img->line;
	if (coord.x > 0 && coord.y > 0 &&
		coord.x < img->size.x && coord.y < img->size.y)
		i[coord.y * img->size.x + coord.x] =
			(color.red << 16 | color.green << 8 | color.blue);
}
