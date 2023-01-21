/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2023/01/15 23:23:29 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define INTERSECTION_FOUND 1
# define DOOR_FOUND 2
# define CELL_SIZE 500
# define FOV 60
# define HALF_FOV 30
# define ANG_IN_D 0.05555555555
# define N 0
# define E 90
# define S 180
# define W 270
# define WIN_W 1080
# define WIN_H 520
# define N_RAY WIN_W
# define OPEN 3
# define CLOSE 4

typedef struct s_map
{
	char			**map_tab;
	int				map_h;
	int				map_w;
}	t_map;

typedef struct s_position
{
	int		x_cell;
	int		y_cell;
	double	virtual_px;
	double	virtual_py;
	double	pov;
	t_map	*map;
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

#endif