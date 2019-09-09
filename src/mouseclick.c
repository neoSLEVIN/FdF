/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseclick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:18:50 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/07 19:24:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouseclick(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	++x;
	++y;
	if (button == 4)
		fdf->cellsize += 1;
	if (button == 5)
		if (fdf->cellsize > 1)
			fdf->cellsize -= 1;
	draw(fdf);
	return (0);
}
