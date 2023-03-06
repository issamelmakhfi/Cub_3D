/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:19:25 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/06 15:57:38 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	player_rotaion(t_mlx *mlx)
{
	if (mlx->pos->right_arrow)
	{
		mlx->pos->pov += 2;
		if (mlx->pos->pov >= 360)
		{
			mlx->pos->pov = 0;
		}
	}
	if (mlx->pos->left_arrow)
	{
		mlx->pos->pov -= 2;
		if (mlx->pos->pov < 0)
			mlx->pos->pov += 360;
	}
}

void	mini_map_zoom(t_mlx *mlx)
{
	if (mlx->pos->mini_map_)
	{
		mlx->pos->b_cells = mlx->info->cell_size_map * 0.5;
		mlx->pos->space = 0.8;
	}
}

int	map_collisions2(t_mlx *mlx, int cx, int cy)
{
	int	x;
	int	y;

	x = cx / mlx->info->cell_size;
	y = cy / mlx->info->cell_size;
	mlx->cx = mlx->pos->x_cell;
	mlx->cy = mlx->pos->y_cell;
	if (case1(mlx, x, y))
		return (1);
	if (case2(mlx, x, y))
		return (1);
	if (case3(mlx, x, y))
		return (1);
	if (case4(mlx, x, y))
		return (1);
	if (mlx->info->map_arr[y][x] && mlx->info->map_arr[y][x] == '1')
		return (1);
	return (0);
}
