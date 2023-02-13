/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 23:59:50 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	keyup(int code, t_mlx *mlx)
{
	printf("here3\n");
	if (code == DOWN_ARROW)
		mlx->pos->down_arrow = 0;
	if (code == UP_ARROW)
		mlx->pos->up_arrow = 0;
	if (code == LEFT_ARROW)
		mlx->pos->left_arrow = 0;
	if (code == RIGHT_ARROW)
		mlx->pos->right_arrow = 0;
	return (0);
}

int	move_player(t_mlx *mlx)
{
	printf("here1\n");
	if (mlx->pos->down_arrow)
		mlx->pos->y_cell++;
	if (mlx->pos->up_arrow)
		mlx->pos->y_cell--;
	if (mlx->pos->left_arrow)
		mlx->pos->x_cell--;
	if (mlx->pos->right_arrow)
		mlx->pos->x_cell++;
	return (0);
}

int	keypress(int code, t_mlx *mlx)
{
	printf("here\n");
	if (code == 53)
		exit(0);
	if (code == DOWN_ARROW)
		mlx->pos->down_arrow = 1;
	if (code == UP_ARROW)
		mlx->pos->up_arrow = 1;
	if (code == LEFT_ARROW)
		mlx->pos->left_arrow = 1;
	if (code == RIGHT_ARROW)
		mlx->pos->right_arrow = 1;
	// miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}

int	key_move(t_mlx *mlx)
{
	move_player(mlx);
	miniMap(mlx->info, mlx->pos, mlx);
	return (0);
}

void	start_execution(t_info *info, t_position *pos, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
    mlx->data.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIN_W, WIN_H, "Cub3D");
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);
	if ((WIN_H / info->map_h) < (WIN_W / info->map_w))
		info->cell_size = WIN_H / info->map_h;
	else
		info->cell_size = WIN_W / info->map_w;
	mlx->info = info;
	mlx->pos = pos;
    miniMap(info, pos, mlx);
	mlx_hook(mlx->win_ptr, 2, 0, keypress, mlx);
	mlx_hook(mlx->win_ptr, 2, (1L<<1), keyup, mlx);
	mlx_loop_hook(mlx->ptr, key_move, mlx);
	// mlx_key_hook(mlx->win_ptr, keey_move, mlx);
    mlx_loop(mlx->ptr);
}