/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawingUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:11:53 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 01:09:35 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	get_texture_color(t_mlx *mlx, int y, int i)
{
	t_image	tmp_image;

	if (mlx->pos->povTextur == E)
		tmp_image = mlx->textur.E_img;
	if (mlx->pos->povTextur == N)
		tmp_image = mlx->textur.N_img;
	if (mlx->pos->povTextur == S)
		tmp_image = mlx->textur.S_img;
	if (mlx->pos->povTextur == W)
		tmp_image = mlx->textur.W_img;
	y = y * (double)tmp_image.y / mlx->pos->wallHeight;
	mlx->pos->offset = get_offset(mlx->rays[i].first, mlx->rays[i].x_save, \
		mlx->rays[i].y_save, tmp_image.x);
	if (mlx->pos->offset > tmp_image.x || y > tmp_image.y \
	|| mlx->pos->offset < 0 || y < 0)
		return ;
	mlx->info->color = tmp_image.addr[y * tmp_image.x + mlx->pos->offset];
}

void	dda(t_mlx *mlx, int x1, int y1)
{
	t_dda	*dda;
	int		i;

	dda = malloc(sizeof(t_dda));
	i = 0;
	dda->dx = x1 - (mlx->pos->virtual_px * mlx->pos->adapter);
	dda->dy = y1 - (mlx->pos->virtual_py * mlx->pos->adapter);
	if (abs(dda->dx) > abs(dda->dy))
		dda->steps = abs(dda->dx);
	else
		dda->steps = abs(dda->dy);
	dda->x_inc = dda->dx / (float)dda->steps;
	dda->y_inc = dda->dy / (float)dda->steps;
	dda->x_ = mlx->pos->virtual_px * mlx->pos->adapter;
	dda->y_ = mlx->pos->virtual_py * mlx->pos->adapter;
	while (i <= dda->steps)
	{
		my_mlx_pixel_put(&mlx->data, dda->x_ * mlx->pos->space, \
		dda->y_ * mlx->pos->space, 0xFF0000);
		dda->x_ += dda->x_inc;
		dda->y_ += dda->y_inc;
		i++;
	}
}

void	draw_cell(t_mlx *mlx)
{
	mlx->x = 0;
	while (mlx->x < WIN_W)
	{
		mlx->y = 0;
		while (mlx->y < WIN_H / 2)
		{
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, 0x000000);
			mlx->y++;
		}
		mlx->x++;
	}
	mlx->x = 0;
	while (mlx->x < WIN_W)
	{
		mlx->y = WIN_H / 2;
		while (mlx->y < WIN_H)
		{
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, 0xdfeaff);
			mlx->y++;
		}
		mlx->x++;
	}
}

void	draw_point(t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	double	a;

	i = -1;
	x = mlx->pos->virtual_px * mlx->pos->adapter;
	y = mlx->pos->virtual_py * mlx->pos->adapter;
	while (++i < 5)
	{
		a = -1;
		while (++a < 360)
		{
			x = i * mlx->table->cos_table[(int)(a / ANG_IN_D)] + \
			(mlx->pos->virtual_px * mlx->pos->adapter);
			y = i * mlx->table->sin_table[(int)(a / ANG_IN_D)] + \
			(mlx->pos->virtual_py * mlx->pos->adapter);
			my_mlx_pixel_put(&mlx->data, x * mlx->pos->space, \
				y * mlx->pos->space, 0xFF0000);
		}
	}
}
