/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 01:27:41 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/14 17:54:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*new_image(t_fdf **fdf, t_point size)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		error("No memory allocated for new image");
	if (!(img->img_ptr = mlx_new_image((*fdf)->mlx_ptr, size.x, size.y)))
		error("Failed to create a new image");
	img->line = mlx_get_data_addr(img->img_ptr,
								&img->bpp, &img->size_line, &img->endian);
	img->size = size;
	return (img);
}

void	clear_img(t_img *img)
{
	int	x;
	int	y;
	int	*convert;

	if (img == NULL)
		return ;
	convert = (int*)img->line;
	y = -1;
	while (++y < img->size.y)
	{
		x = -1;
		while (++x < img->size.x)
			convert[y * img->size.x + x] = 0;
	}
}
