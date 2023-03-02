/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawingUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:11:53 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 22:12:22 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

t_image	set_textur(t_mlx *mlx)
{
	if (mlx->pos->pov_textur == E)
		return (mlx->textur.e_img);
	if (mlx->pos->pov_textur == N)
		return (mlx->textur.n_img);
	if (mlx->pos->pov_textur == S)
		return (mlx->textur.s_img);
	if (mlx->pos->pov_textur == W)
		return (mlx->textur.w_img);
	return (mlx->textur.w_img);
}

void	get_texture_color(t_mlx *mlx, int tex_y, int i)
{
	t_image	tmp_image;
	double	tex_dy;
	double	tex_dx;

	tex_dy = 0;
	tex_dx = 0;
	tmp_image = set_textur(mlx);
	tex_dy = tex_y;
	if (tex_dy < 0)
		tex_dy = 0;
	tex_dx = mlx->rays[i].x_save;
	if (mlx->rays[i].first == 'v')
		tex_dx = mlx->rays[i].y_save;
	tex_dx /= CELL_SIZE;
	tex_dx -= floor(tex_dx);
	tex_dx *= tmp_image.x;
	tex_dy *= (double)tmp_image.y / mlx->pos->wall_height;
	tex_dy = floor(tex_dy);
	tex_dy *= tmp_image.x;
	mlx->info->color = tmp_image.addr[(int)tex_dy + (int)tex_dx];
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
		dda->y_ * mlx->pos->space, 0xFCC99FF);
		dda->x_ += dda->x_inc;
		dda->y_ += dda->y_inc;
		i++;
	}
	free(dda);
}

void	draw_cell(t_mlx *mlx)
{
	mlx->x = 0;
	while (mlx->x < WIN_W)
	{
		mlx->y = 0;
		while (mlx->y < WIN_H / 2)
		{
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, mlx->info->c_color);
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
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, mlx->info->f_color);
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
				y * mlx->pos->space, 0xFCC99FF);
		}
	}
}
