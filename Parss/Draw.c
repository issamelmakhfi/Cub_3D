/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 21:05:41 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	keyup(int code, t_mlx *mlx)
{
	if (code == SPACE)
	{
		mlx->pos->b_cells = mlx->info->cell_size_map * 1;
		mlx->pos->mini_map_ = 0;
		mlx->pos->space = 0.3;
	}
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
		mlx->pos->up_arrow = 0;
	if (code == LEFT_ARROW)
		mlx->pos->left_arrow = 0;
	if (code == RIGHT_ARROW)
		mlx->pos->right_arrow = 0;
	return (0);
}

int	key_press(int code, t_mlx *mlx)
{
	if (code == SPACE)
		mlx->pos->mini_map_ = 1;
	if (code == EXIT)
		exit(0);
	if (code == _W)
		mlx->pos->_w = 1;
	if (code == _A)
		mlx->pos->_a = 1;
	if (code == _S)
		mlx->pos->_s = 1;
	if (code == _D)
		mlx->pos->_d = 1;
	if (code == LEFT_ARROW)
		mlx->pos->left_arrow = 1;
	if (code == RIGHT_ARROW)
		mlx->pos->right_arrow = 1;
	return (0);
}

int	key_handler(t_mlx *mlx)
{
	int	x_save;
	int	y_save;
	int	x_;
	int	y_;

	x_save = mlx->pos->virtual_px;
	y_save = mlx->pos->virtual_py;
	if (player_move(mlx, x_save, y_save))
		return (1);
	mini_map_zoom(mlx);
	x_ = mlx->pos->virtual_px / CELL_SIZE;
	y_ = mlx->pos->virtual_py / CELL_SIZE;
	if (mlx->info->map_arr[y_][x_] && mlx->info->map_arr[y_][x_] == '1')
		return (1);
	mlx->pos->x_cell = mlx->pos->virtual_px / CELL_SIZE;
	mlx->pos->y_cell = mlx->pos->virtual_py / CELL_SIZE;
	clear_draw(&mlx);
	casting_rays(mlx->table, mlx->rays, mlx->pos);
	map_projection(mlx);
	mini_map(mlx);
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	(void)y;
	if (x >= WIN_W)
		x = 0;
	if (x <= 0)
		x = WIN_W;
	if ((x - mlx->pos->old_x) > 0)
	{
		mlx->pos->pov += 2;
		if (mlx->pos->pov >= 360)
			mlx->pos->pov = 0;
	}
	else if ((x - mlx->pos->old_x) < 0)
	{
		mlx->pos->pov -= 2;
		if (mlx->pos->pov <= 0)
			mlx->pos->pov += 360;
	}
	mlx->pos->old_x = x;
	return (0);
}

void	start_execution(t_info *info, t_position *pos, t_mlx *mlx)
{
	t_table	*table;
	t_ray	rays[N_RAY];

	table = malloc(sizeof(t_table));
	pos->info = info;
	mlx->ptr = mlx_init();
	mlx->data.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIN_W, WIN_H, "Cub3D");
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, \
	&mlx->data.bits_per_pixel, \
	&mlx->data.line_length, &mlx->data.endian);
	create_trigonometric_tables(6480, table, 0);
	casting_rays(table, rays, pos);
	mlx->info = info;
	mlx->pos = pos;
	mlx->rays = rays;
	mlx->table = table;
	xpm_image(mlx);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), &key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, (1L << 1), &keyup, mlx);
	mlx_hook(mlx->win_ptr, 06, 0L, &mouse_move, mlx);
	mlx_loop_hook(mlx->ptr, &key_handler, mlx);
	mlx_loop(mlx->ptr);
}
