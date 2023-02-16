/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/16 23:33:22 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void clear_draw(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->data.img);
	mlx->data.img = mlx_new_image(mlx->ptr, WIN_H, WIN_W);
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);
}

int	keyup(int code, t_mlx *mlx)
{
	if (code == _W)
		mlx->pos->_w = 0;
	if (code == _A)
		mlx->pos->_a = 0;
	if (code == _S)
		mlx->pos->_s = 0;
	if (code == _D)
		mlx->pos->_d = 0;
	if (code == DOWN_ARROW)
		mlx->pos->down_arrow = 0;
	if (code == UP_ARROW)
	{
		mlx->pos->up_arrow = 0;
	}
	if (code == LEFT_ARROW)
	{
		// printf("LLLLLLLLLL\n");
		mlx->pos->left_arrow = 0;
		mlx->pos->turnDirection = 0;
	}
	if (code == RIGHT_ARROW)
	{
		printf("LLLLLLLLLL\n");
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + 0.5;
		// mlx->pos->right_arrow = 0;
		// mlx->pos->turnDirection = 0;
	}
	miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}

int	keyD(int code, t_mlx *mlx)
{
	if (code == _W)
		mlx->pos->_w = 1;
	if (code == _A)
		mlx->pos->_a = 1;
	if (code == _S)
		mlx->pos->_s = 1;
	if (code == _D)
		mlx->pos->_d = 1;
	if (code == DOWN_ARROW)
		mlx->pos->down_arrow = 1;
	if (code == UP_ARROW)
		mlx->pos->up_arrow = 1;
	if (code == LEFT_ARROW)
	{
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + (-1 * 0.2);
		// mlx->pos->left_arrow = 1;
		// mlx->pos->turnDirection = -1;
	}
	if (code == RIGHT_ARROW)
	{
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + 0.2;
		// mlx->pos->right_arrow = 1;
		// mlx->pos->turnDirection = 1;
	}
	
	miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}

int	keypress(t_mlx *mlx)
{
	int Cx = 0;
	int	Cy = 0;
	if (mlx->pos->_s)
	{
		Cy = ((mlx->pos->virtual_py + 5) / mlx->info->cell_size);
		printf("%d %d\n", Cx, Cy);
		if (mlx->info->map_arr[Cy][mlx->pos->x_cell] == '1')
			return 1;
		mlx->pos->virtual_py += 5;
	}
	if (mlx->pos->_w)
	{
		Cy = ((mlx->pos->virtual_py - 5) / mlx->info->cell_size);
		if (mlx->info->map_arr[Cy][mlx->pos->x_cell] == '1')
			return 1;
		mlx->pos->virtual_py -= 5;
	}
	if (mlx->pos->_a)
	{
		Cx = ((mlx->pos->virtual_px - 5) / mlx->info->cell_size);
		if (mlx->info->map_arr[mlx->pos->y_cell][Cx] == '1')
			return 1;
		mlx->pos->virtual_px -= 5;
	}
	if (mlx->pos->_d)
	{
		Cx = ((mlx->pos->virtual_px + 5) / mlx->info->cell_size);
		if (mlx->info->map_arr[mlx->pos->y_cell][Cx] == '1')
			return 1;
		mlx->pos->virtual_px += 5;
	}
	if (mlx->pos->right_arrow)
	{
		// printf("HERE\n");
		mlx->pos->rotationAngle += mlx->pos->turnDirection * mlx->pos->rotationSpeed;
		printf("%f\n", mlx->pos->rotationAngle);
	}
	if (mlx->pos->left_arrow)
	{
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + 0.000000000000000000005;
	}
	mlx_destroy_image(mlx->ptr, mlx->data.img);
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);
	miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}


void	start_execution(t_info *info, t_position *pos, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
    mlx->data.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIN_W, WIN_H, "Cub3D");
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);

	mlx->info = info;
	mlx->pos = pos;
	mlx->pos->rotationAngle = 0;
    miniMap(info, pos, mlx);
	// wallProjection(mlx);
	// clear_draw(mlx);
	clear_draw(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L<<0), keyD, mlx);
	// mlx_hook(mlx->win_ptr, 3, (1L<<1), keyup, mlx);
	// mlx_loop_hook(mlx->ptr, keypress, mlx);
    mlx_loop(mlx->ptr);
}