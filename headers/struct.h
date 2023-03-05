/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2023/03/05 18:33:09 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define INTERSECTION_FOUND 1
# define DOOR_FOUND 2
# define CELL_SIZE 50
# define FOV 60
# define HALF_FOV 30
# define ANG_IN_D 0.05555555555
# define N 0
# define E 90
# define S 180
# define W 270
# define F -1
# define WIN_W 1080
# define WIN_H 520
# define N_RAY WIN_W
# define OPEN 3
# define CLOSE 4
# define LEFT_ARROW		123
# define RIGHT_ARROW	124
# define DOWN_ARROW		125
# define UP_ARROW		126

# define _W 13
# define _A 0
# define _S 1
# define _D 2
# define EXIT 53
# define SPACE 49
# define PI 3.142857
# define RED 0xFF0000

typedef struct s_data
{
	void	*img;
	void	*xpm_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	char			*map_tab;
	char			*elements;
	int				check;
	struct s_map	*next;
}	t_map;

typedef struct s_info
{
	char			**map_arr;
	char			**elements;
	int				map_h;
	int				map_w;
	int				cell_size;
	int				cell_size_map;
	char			*path_n;
	char			*path_s;
	char			*path_e;
	char			*path_w;
	unsigned int	c_color;
	unsigned int	f_color;
	int				r;
	int				g;
	int				b;
	char			*texture;
	int				color;
	t_map			*map;
}	t_info;

typedef struct s_position
{
	int		x_cell;
	int		y_cell;
	double	virtual_px;
	double	virtual_py;
	double	map_px;
	double	map_py;
	double	pov;
	int		pov_textur;
	int		down_arrow;
	int		up_arrow;
	int		left_arrow;
	int		right_arrow;
	int		_w;
	int		_a;
	int		_s;
	int		_d;
	double	space;
	int		mini_map_;
	int		b_cells;
	int		wall_color;
	int		wall_height;
	int		offset;
	double	dis;
	int		top_pixel;
	double	adapter;
	int		old_x;
	int		old_y;
	t_info	*info;
}	t_position;

typedef struct s_ray
{
	int			door;
	int			first;
	int			v_skip;
	int			h_skip;
	double		x_save;
	double		y_save;
	double		ray_pov;
	int			index;
	double		xi ;
	double		yi ;
	double		xbound ;
	double		ybound;
	int			v_hit;
	int			h_hit;
	double		v_distance;
	double		h_distance;
	double		x_step;
	double		y_step;
	int			quadrant;
	int			xcell_v;
	int			ycell_v;
	int			xcell_h;
	int			ycell_h;
	double		save_distance;
	double		ray_h;
	t_position	*player;
}				t_ray;
typedef struct s_table
{
	double	*tan_table;
	double	*cos_table;
	double	*sin_table;
}				t_table;

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_image;
typedef struct s_texter
{
	t_image	e_img;
	t_image	n_img;
	t_image	s_img;
	t_image	w_img;
}	t_texter;

typedef struct s_dda
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x_;
	float	y_;
}	t_dda;
typedef struct s_mlx
{
	void		*ptr;
	void		*win_ptr;
	int			color;
	int			x;
	int			y;
	int			cx;
	int			cy;
	t_info		*info;
	t_data		data;
	t_ray		*rays;
	t_position	*pos;
	t_table		*table;
	t_image		image;
	t_texter	textur;
}	t_mlx;

typedef struct s_tmp
{
	t_mlx	*mlx;
}	t_tmp;

#endif