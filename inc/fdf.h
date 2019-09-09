/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:33:26 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/09 23:30:41 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_X 1000
# define WIN_Y 1000
# define CELLSIZE 2
# define DEGREE 3

# define WRONG_CNT -1
# define ERR_EXIT 1
# define COLOR 1
# define INT 2
# define PI 3.14159265

# define F_DEG 1
# define F_SIZ 2
# define F_GRD 4
# define F_COL 8

# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"
/*
# include "macoskeys.h"
*/
# include "linuxkeys.h"

typedef enum		e_projection
{
	FREE,
	TRUE_ISO,
	TWO_ONE_ISO
}					t_proj;

typedef struct		s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_rgb;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_dpoint
{
	double			x;
	double			y;
	double			z;
}					t_dpoint;

typedef struct		s_gradient
{
	int				col_cnt;
	t_rgb			col[11];
	double			range[11];
}					t_grad;

typedef struct		s_mappoint
{
	t_dpoint		coord;
	t_rgb			*view_color;
	t_rgb			default_color;
	t_rgb			custom_color;
	double			z;
}					t_mappoint;

typedef struct		s_map
{
	t_mappoint		**map;
	t_mappoint		**view;
	t_point			size;
	t_proj			projection;
	double			max;
	double			min;
	int				col_mode;
	t_dpoint		center;
	t_dpoint		drawcenter;
	t_grad			grad;
}					t_map;

typedef struct		s_cam
{
	t_point			coord;
	t_dpoint		angle;
	double			degree;
	int				speed;
}					t_cam;

typedef struct		s_img
{
	void			*img_ptr;
	t_point			size;
	char			*line;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_win
{
	void			*win_ptr;
	int				x_win;
	int				y_win;
	char			*title;
}					t_win;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	t_win			*win;
	t_img			*img;
	t_cam			cam;
	t_map			*map;
	int				cellsize;
	int				ui;
}					t_fdf;

typedef struct		s_flag
{
	int				flag;
	int				args;
	int				deg;
	int				col_cnt;
	int				size[2];
	int				grad[9];
	t_rgb			col[11];
	_Bool			help;
}					t_flg;

int					lite_usage(char *app_name);
int					usage(char *app_name);
int					error(char *err_msg);
int					diff_size_err(int line);
int					empty_line_err(int line);
int					wrong_line_err(int line, int word, int type);
int					err_usage(char *err_msg, char *app_name, _Bool full);

int					atoi16(char *num, int isonechar);
int					is_int(char *num);
int					is_hex(char *hex);
int					is_move(int key);
int					is_rotate(int key);
void				hex_to_rgb(char *hex, t_rgb *color);
void				valid_line(char **word_split, int line);
void				valid_stdin(t_flg *flg, int ac, char **av);

t_win				*new_window(t_fdf **fdf, int x_win, int y_win, char *title);
t_img				*new_image(t_fdf **fdf, t_point size);
t_map				*new_map(int fd);
t_mappoint			**new_view(t_map *map);

t_rgb				set_rgb(int red, int green, int blue);
t_point				set_point(int x, int y, int z);
t_dpoint			set_dpoint(double x, double y, double z);
void				set_grad_colors(t_map *map, t_flg *flg);
void				set_point_color(char *word, t_mappoint **map, int x, int y);
void				set_custom_color(t_map *map);
t_rgb				get_grad_color(t_map *map, double z);

void				clear_img(t_img *img);
void				del_map(char **map);

void				switch_projection(t_fdf **fdf);
void				switch_color(t_map *map);
void				col_grad(t_flg *flg, int ac, char **av, int i);
void				draw(t_fdf *fdf);
void				draw_map(t_fdf *fdf);
void				draw_line(t_fdf *fdf, t_mappoint start, t_mappoint end);
void				draw_ui(t_fdf *fdf);
void				plot(t_img *img, t_rgb color, t_point coord);
void				rotate_fdf(t_fdf *fdf);
void				rotate_x(t_dpoint *point, t_dpoint *center, double angle);
void				rotate_y(t_dpoint *point, t_dpoint *center, double angle);
void				rotate_z(t_dpoint *point, t_dpoint *center, double angle);
int					mouseclick(int button, int x, int y, void *param);
int					deal_key(int key, void *param);
int					red_x_button(void *param);

#endif
