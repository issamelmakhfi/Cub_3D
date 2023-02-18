/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/18 19:38:19 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void clear_draw(t_mlx **mlx)
{
	
	mlx_destroy_image((*mlx)->ptr, (*mlx)->data.img);
	(*mlx)->data.img = mlx_new_image((*mlx)->ptr, WIN_W, WIN_H);
	(*mlx)->data.addr = mlx_get_data_addr((*mlx)->data.img, &(*mlx)->data.bits_per_pixel, &(*mlx)->data.line_length, &(*mlx)->data.endian);
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
		mlx->pos->left_arrow = 0;
		mlx->pos->turnDirection = 0;
	}
	if (code == RIGHT_ARROW)
	{
		mlx->pos->right_arrow = 0;
		mlx->pos->turnDirection = 0;
	}
	return (0);
}

int	keyD(int code, t_mlx *mlx)
{
	if (code == 53)
		exit(0);
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
		mlx->pos->left_arrow = 1;
	}
	if (code == RIGHT_ARROW)
	{
		mlx->pos->right_arrow = 1;
	}
	return (0);
}

int	map_collisions(t_mlx *mlx, int Cx, int Cy)
{
	int	X;
	int	Y;
	
	// if (Cx < 0 || Cx > WIN_W || Cy < 0 || Cy > WIN_H)
	// 	return 1;
	X = Cx / mlx->info->cell_size;
	Y = Cy / mlx->info->cell_size;
	if (mlx->info->map_arr[Y][X] && mlx->info->map_arr[Y][X] == '1')
		return 1;
	return 0;
}

int	keypress(t_mlx *mlx)
{
	int Cx = 0;
	int	Cy = 0;
	if (mlx->pos->_s)
	{
		Cy = mlx->pos->virtual_py + (cos(mlx->pos->rotationAngle) * 5);
		Cx = mlx->pos->virtual_px + (sin(mlx->pos->rotationAngle) * 5);
		if (map_collisions(mlx, Cx, Cy))
			return 1;
		mlx->pos->virtual_py = mlx->pos->virtual_py + (cos(mlx->pos->rotationAngle) * 5);
		mlx->pos->virtual_px = mlx->pos->virtual_px + (sin(mlx->pos->rotationAngle) * 5);
	}
	if (mlx->pos->_w)
	{
		Cy = mlx->pos->virtual_py - (cos(mlx->pos->rotationAngle) * 5);
		Cx = mlx->pos->virtual_px - (sin(mlx->pos->rotationAngle) * 5);
		if (map_collisions(mlx, Cx, Cy))
			return 1;
		mlx->pos->virtual_py = mlx->pos->virtual_py - (cos(mlx->pos->rotationAngle) * 5);
		mlx->pos->virtual_px = mlx->pos->virtual_px - (sin(mlx->pos->rotationAngle) * 5);
		// printf("%d\n", mlx->info->cell_size);
		// printf("%f %f\n", mlx->pos->virtual_px, mlx->pos->virtual_py);
	}
	if (mlx->pos->_a)
	{
		Cx = mlx->pos->virtual_px - (cos(mlx->pos->rotationAngle) * 5);
		if (map_collisions(mlx, Cx, mlx->pos->virtual_py))
			return 1;
		mlx->pos->virtual_px = mlx->pos->virtual_px - (cos(mlx->pos->rotationAngle) * 5);
	}
	if (mlx->pos->_d)
	{
		Cx = mlx->pos->virtual_px + (cos(mlx->pos->rotationAngle) * 5);
		if (map_collisions(mlx, Cx, mlx->pos->virtual_py))
			return 1;
		mlx->pos->virtual_px = mlx->pos->virtual_px + (cos(mlx->pos->rotationAngle) * 5);
	}
	if (mlx->pos->right_arrow)
	{
			mlx->pos->rotationAngle = mlx->pos->rotationAngle + (-1 * 0.09);
	}
	if (mlx->pos->left_arrow)
	{
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + (1 * 0.09);
	}
	clear_draw(&mlx);
	miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}


int	mouse_move(int x, int y, t_mlx *mlx)
{
	(void)y;
	if (x > 0 && x < WIN_W)
	{
		mlx_mouse_hide();
		mlx->pos->rotationAngle = mlx->pos->rotationAngle + (((WIN_W/2) - x) * (M_PI / 180)) / 20;
		mlx_mouse_move(mlx->win_ptr, WIN_W / 2, WIN_H / 2);
		mlx->pos->tmpX = WIN_W / 2;
		// exit(0);
	}
	return 0;	
}

void	start_execution(t_info *info, t_position *pos, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
    mlx->data.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIN_W, WIN_H, "Cub3D");
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);

	mlx->info = info;
	mlx->pos = pos;
	mlx->pos->rotationAngle = mlx->pos->pov * (M_PI / 180);
    miniMap(info, pos, mlx);
	mlx_hook(mlx->win_ptr, 2, (1L<<0), keyD, mlx);
	mlx_hook(mlx->win_ptr, 3, (1L<<1), keyup, mlx);
	// mlx_hook(mlx->win_ptr, 6, 0L,&mouse_move, mlx);
	
	mlx_loop_hook(mlx->ptr, keypress, mlx);
    mlx_loop(mlx->ptr);
}