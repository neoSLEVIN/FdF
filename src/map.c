/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 03:48:40 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/04 21:48:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** main[0],gnl[1],ptr[2]
** gnl_ret_res[0],wordcnt[1]
** x_words[0],y_lines[1]
*/

#include "fdf.h"

static void			set_min_max(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	map->min = map->map[0][0].coord.z;
	map->max = map->map[0][0].coord.z;
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			map->map[y][x].coord.z < map->min ?
				map->min = map->map[y][x].coord.z : 0;
			map->map[y][x].coord.z > map->max ?
				map->max = map->map[y][x].coord.z : 0;
		}
	}
}

static t_mappoint	**set_mappoints(char **line_split, int words, int lines)
{
	char		**word_split;
	t_mappoint	**map;
	int			x;
	int			y;

	y = -1;
	if (!(map = (t_mappoint**)malloc(sizeof(t_mappoint*) * lines)))
		error("No memory allocated for new map");
	while (++y < lines)
	{
		x = -1;
		if (!(word_split = ft_strstrsplit(line_split[y], " \t")))
			error("No memory allocated for splitting words");
		valid_line(word_split, y);
		if (!(map[y] = (t_mappoint*)malloc(sizeof(t_mappoint) * words)))
			error("No memory allocated for new point on map");
		while (++x < words)
			set_point_color(word_split[x], map, x, y);
		del_map(word_split);
	}
	del_map(line_split);
	return (map);
}

static void			make_str(int fd, char **str, int *coord, int *temp)
{
	temp[1] = ft_wordcnt(str[1], " \t");
	coord[0] = (coord[0] == WRONG_CNT) ? temp[1] : coord[0];
	if (coord[0] != temp[1] || temp[1] == 0)
	{
		close(fd);
		temp[1] == 0 ? empty_line_err(coord[1]) : diff_size_err(coord[1]);
	}
	else
		++coord[1];
	str[2] = str[1];
	if (!(str[1] = ft_strjoin(str[1], "\n")))
	{
		close(fd);
		error("No memory allocated for new string");
	}
	ft_strdel(&str[2]);
	str[2] = str[0];
	if (!(str[0] = ft_strjoin(str[0], str[1])))
	{
		close(fd);
		error("No memory allocated for new string");
	}
	ft_strdel(&str[1]);
	ft_strdel(&str[2]);
}

static t_mappoint	**make_map(int fd, t_map *map)
{
	char	**line_split;
	char	*str[3];
	int		temp[2];
	int		coord[2];

	if (!(str[0] = ft_strnew(0)))
	{
		close(fd);
		error("No memory allocated for new map");
	}
	coord[0] = WRONG_CNT;
	coord[1] = 0;
	while ((temp[0] = get_next_line(fd, &str[1])) == 1)
		make_str(fd, str, coord, temp);
	close(fd);
	temp[0] == -1 ? error("Bad GNL work") : 0;
	coord[1] == 0 ? error("Empty file") : 0;
	map->size = set_point(coord[0], coord[1], 0);
	if (!(line_split = ft_strsplit(str[0], '\n')))
		error("No memory allocated for splitting strings");
	ft_strdel(&str[0]);
	return (set_mappoints(line_split, coord[0], coord[1]));
}

t_map				*new_map(int fd)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
	{
		close(fd);
		error("No memory allocated for new map");
	}
	map->map = make_map(fd, map);
	set_min_max(map);
	return (map);
}
