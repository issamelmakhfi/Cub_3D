/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:19:25 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 17:07:01 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	player_rotaion(t_mlx *mlx)
{
	if (mlx->pos->right_arrow)
	{
		if (mlx->pos->pov > 360)
			mlx->pos->pov = 0;
		mlx->pos->pov += 4;
	}
	if (mlx->pos->left_arrow)
	{
		if (mlx->pos->pov < 0)
			mlx->pos->pov += 360;
		mlx->pos->pov -= 4;
	}
}

void	mini_map_zoom(t_mlx *mlx)
{
	if (mlx->pos->miniMap)
	{
		mlx->pos->b_cells = mlx->info->cell_sizeMap * 0.5;
		mlx->pos->space = 0.8;
	}
}

int	map_collisions(t_mlx *mlx, int Cx, int Cy)
{
	int	x;
	int	y;

	x = roundf(Cx / mlx->info->cell_size);
	y = roundf(Cy / mlx->info->cell_size);
	if (mlx->info->map_arr[y][x] && mlx->info->map_arr[y][x] == '1')
		return (1);
	return (0);
}
