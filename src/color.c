/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 23:18:11 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/28 01:02:42 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hex_to_rgb(char *hex, t_rgb *color)
{
	size_t	len;

	len = ft_strlen(hex);
	if (len == 1)
		*color = set_rgb(atoi16(hex, 1), atoi16(hex, 1), atoi16(hex, 1));
	else if (len == 3)
		*color =
			set_rgb(atoi16(hex, 1), atoi16(&hex[1], 1), atoi16(&hex[2], 1));
	else if (len == 6)
		*color =
			set_rgb(atoi16(hex, 2), atoi16(&hex[2], 2), atoi16(&hex[4], 2));
}

void	set_point_color(char *word, t_mappoint **map, int x, int y)
{
	char	**num_color;

	if (!(num_color = ft_strsplit(word, ',')))
		error("No memory allocated for splitting strings");
	if (!is_int(num_color[0]))
		wrong_line_err(y, x, INT);
	map[y][x].coord = set_dpoint(x, y, ft_atoi(num_color[0]));
	if (ft_strstr(word, ",0x") != NULL)
		hex_to_rgb(num_color[1] + 2, &map[y][x].default_color);
	else
		map[y][x].default_color = set_rgb(255, 255, 255);
	del_map(num_color);
}

t_rgb	get_grad_color(t_map *map, double z)
{
	t_rgb	color;
	double	d_r;
	int		part;

	if (z <= 0)
		return (map->grad.col[0]);
	else if (z >= 1)
		return (map->grad.col[map->grad.col_cnt - 1]);
	else
	{
		part = 0;
		while (++part < map->grad.col_cnt - 1)
			if (z >= map->grad.range[part - 1] && z < map->grad.range[part])
				break ;
	}
	d_r = (z - map->grad.range[part - 1]) /
		(map->grad.range[part] - map->grad.range[part - 1]);
	color.red = map->grad.col[part - 1].red +
		d_r * (map->grad.col[part].red - map->grad.col[part - 1].red);
	color.green = map->grad.col[part - 1].green +
		d_r * (map->grad.col[part].green - map->grad.col[part - 1].green);
	color.blue = map->grad.col[part - 1].blue +
		d_r * (map->grad.col[part].blue - map->grad.col[part - 1].blue);
	return (color);
}

void	set_custom_color(t_map *map)
{
	t_point	p;
	double	z;
	double	delta_z;

	delta_z = map->max - map->min;
	delta_z == 0 ? delta_z = 1 : 0;
	p.y = -1;
	while (++p.y < map->size.y)
	{
		p.x = -1;
		while (++p.x < map->size.x)
		{
			z = (map->map[p.y][p.x].coord.z - map->min) / delta_z;
			map->map[p.y][p.x].custom_color = get_grad_color(map, z);
			if (z <= 0)
				map->map[p.y][p.x].z = 0;
			else if (z >= 1)
				map->map[p.y][p.x].z = 1;
			else
				map->map[p.y][p.x].z = z;
		}
	}
}

void	switch_color(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
			map->view[y][x].view_color = map->col_mode ?
				&map->map[y][x].custom_color : &map->map[y][x].default_color;
	}
	map->col_mode ^= 1;
}
