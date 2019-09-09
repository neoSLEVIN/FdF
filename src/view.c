/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 21:12:58 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/07 21:45:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_mappoint	**new_view(t_map *map)
{
	t_mappoint	**view;
	int			i;

	if (!(view = (t_mappoint**)malloc(sizeof(t_mappoint*) * map->size.y)))
		error("No memory allocated for new view");
	i = -1;
	while (++i < map->size.y)
		if (!(view[i] = (t_mappoint*)malloc(sizeof(t_mappoint) * map->size.x)))
			error("No memory allocated for new view");
	return (view);
}
