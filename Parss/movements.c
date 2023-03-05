/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:51:41 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/04 20:59:58 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	player_move(t_mlx *mlx, int x_save, int y_save)
{
	if (s_move(mlx, x_save, y_save))
		return (1);
	if (w_move(mlx, x_save, y_save))
		return (1);
	if (a_move(mlx, x_save, y_save))
		return (1);
	if (d_move(mlx, x_save, y_save))
		return (1);
	player_rotaion(mlx);
	return (0);
}

int	s_move(t_mlx *mlx, int x_save, int y_save)
{
	if (mlx->pos->_s)
	{
		if (map_collisions2(mlx, x_save - \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4 \
		, y_save + mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4))
			return (1);
		mlx->pos->virtual_px -= \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->virtual_py += \
		mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->map_px += mlx->pos->virtual_px - x_save;
		mlx->pos->map_py += mlx->pos->virtual_py - y_save;
	}
	return (0);
}

int	w_move(t_mlx *mlx, int x_save, int y_save)
{
	if (mlx->pos->_w)
	{
		if (map_collisions2(mlx, x_save + \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4 \
		, y_save - mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4))
			return (1);
		mlx->pos->virtual_px += \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->virtual_py -= \
		mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->map_px += mlx->pos->virtual_px - x_save;
		mlx->pos->map_py += mlx->pos->virtual_py - y_save;
	}
	return (0);
}

int	a_move(t_mlx *mlx, int x_save, int y_save)
{
	if (mlx->pos->_a)
	{
		if (map_collisions2(mlx, x_save - \
		(mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4) \
		, y_save - mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4))
			return (1);
		mlx->pos->virtual_px -= \
		mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->virtual_py -= \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->map_px += mlx->pos->virtual_px - x_save;
		mlx->pos->map_py += mlx->pos->virtual_py - y_save;
	}
	return (0);
}

int	d_move(t_mlx *mlx, int x_save, int y_save)
{
	if (mlx->pos->_d)
	{
		if (map_collisions2(mlx, x_save + \
		(mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4) \
		, y_save + mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4))
			return (1);
		mlx->pos->virtual_py += \
		mlx->table->sin_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->virtual_px += \
		mlx->table->cos_table[(int)(mlx->pos->pov / ANG_IN_D)] * 4;
		mlx->pos->map_px += mlx->pos->virtual_px - x_save;
		mlx->pos->map_py += mlx->pos->virtual_py - y_save;
	}
	return (0);
}
