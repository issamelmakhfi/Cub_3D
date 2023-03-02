/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 00:23:52 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "../42Get_next_line/get_next_line.h"
# include "../42Libft/libft.h"
# include "cub3d.h"

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

void	init_data(t_info *info, t_position *pos);
void	clear_draw(t_mlx **mlx);
void	map_projection(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	xpm_image(t_mlx *mlx);
void	get_texture_color(t_mlx *mlx, int y, int i);
void	dda(t_mlx *mlx, int x1, int y1);
void	draw_cell(t_mlx *mlx);
void	draw_point(t_mlx *mlx);
int		get_offset(int direction, int x, int y, int img_x);
int		abs(int n);
void	get_pov(t_mlx *mlx, int i);
void	project_wall(t_mlx *mlx, int i);
int		map_collisions(t_mlx *mlx, int cx, int cy);

//////////////////////////////// Movements //////////////////////////

int		player_move(t_mlx *mlx, int x_save, int y_save);
int		s_move(t_mlx *mlx, int x_save, int y_save);
int		w_move(t_mlx *mlx, int x_save, int y_save);
int		a_move(t_mlx *mlx, int x_save, int y_save);
int		d_move(t_mlx *mlx, int x_save, int y_save);
void	player_rotaion(t_mlx *mlx);
void	mini_map_zoom(t_mlx *mlx);
int		keey_move(int code, t_mlx *mlx);

#endif