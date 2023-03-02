/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawingUtils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:18:33 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 00:50:59 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	project_wall(t_mlx *mlx, int i)
{
	int	j;

	j = 0;
	if (((WIN_H - mlx->pos->wallHeight) / 2) <= 0)
		j = -1 * (((WIN_H - mlx->pos->wallHeight) / 2));
	while (j < mlx->pos->wallHeight)
	{
		get_texture_color(mlx, j, i);
		mlx->pos->top_pixel = ((WIN_H - mlx->pos->wallHeight) / 2) + j;
		if (mlx->pos->top_pixel > WIN_H)
			break ;
		my_mlx_pixel_put(&mlx->data, i, mlx->pos->top_pixel, mlx->info->color);
		j++;
	}
}

void	get_pov(t_mlx *mlx, int i)
{
	if (mlx->rays[i].first == 'v')
	{
		if (mlx->rays[i].ray_pov >= 0 && mlx->rays[i].ray_pov <= 180)
			mlx->pos->povTextur = E;
		if (mlx->rays[i].ray_pov >= 180 && mlx->rays[i].ray_pov <= 360)
			mlx->pos->povTextur = W;
	}
	else if (mlx->rays[i].first == 'h')
	{
		if ((mlx->rays[i].ray_pov >= 0 && mlx->rays[i].ray_pov <= 90) || \
			(mlx->rays[i].ray_pov >= 270 && mlx->rays[i].ray_pov < 360))
			mlx->pos->povTextur = N;
		else
			mlx->pos->povTextur = S;
	}
}

int	get_offset(int direction, int x, int y, int img_x)
{
	if (direction == 'v')
		return (y % CELL_SIZE * ((double)img_x / CELL_SIZE));
	else
		return (x % CELL_SIZE * ((double)img_x / CELL_SIZE));
}

int	abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * (-1));
}
