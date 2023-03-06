/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:26:54 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/04 01:28:02 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	case1(t_mlx *mlx, int x, int y)
{
	if (mlx->info->map_arr[mlx->cy - 1][mlx->cx] == '1' \
	&& mlx->info->map_arr[mlx->cy][mlx->cx + 1] == '1')
	{
		if (mlx->info->map_arr[y][x - 1] == '1' \
		&& mlx->info->map_arr[y + 1][x] == '1')
			return (1);
	}
	return (0);
}

int	case2(t_mlx *mlx, int x, int y)
{
	if (mlx->info->map_arr[mlx->cy + 1][mlx->cx] == '1' \
	&& mlx->info->map_arr[mlx->cy][mlx->cx - 1] == '1')
	{
		if (mlx->info->map_arr[y][x + 1] == '1' \
		&& mlx->info->map_arr[y - 1][x] == '1')
			return (1);
	}
	return (0);
}

int	case3(t_mlx *mlx, int x, int y)
{
	if (mlx->info->map_arr[mlx->cy - 1][mlx->cx] == '1' \
	&& mlx->info->map_arr[mlx->cy][mlx->cx - 1] == '1')
	{
		if (mlx->info->map_arr[y][x + 1] == '1' \
		&& mlx->info->map_arr[y + 1][x] == '1')
			return (1);
	}
	return (0);
}

int	case4(t_mlx *mlx, int x, int y)
{
	if (mlx->info->map_arr[mlx->cy + 1][mlx->cx] == '1' \
	&& mlx->info->map_arr[mlx->cy][mlx->cx + 1] == '1')
	{
		if (mlx->info->map_arr[y][x - 1] == '1' \
		&& mlx->info->map_arr[y - 1][x] == '1')
			return (1);
	}
	return (0);
}
