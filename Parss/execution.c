/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:42:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 15:47:35 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	keey_move(int code, t_mlx *mlx)
{
	printf("%d\n", code);
	if (code == DOWN_ARROW)
		mlx->y += 1;
	if (code == 53)
		exit(0);
	mlx->color = 0xFF0000;
	draw(&mlx->data, mlx->info, mlx);
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
    miniMap(info, pos, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
	mlx_key_hook(mlx->win_ptr, keey_move, mlx);
    mlx_loop(mlx->ptr);
}