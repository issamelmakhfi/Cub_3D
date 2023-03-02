/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:20:33 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 00:33:35 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	xpm_image(t_mlx *mlx)
{
	mlx->textur.E_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_E, \
		&mlx->textur.E_img.x, &mlx->textur.E_img.y);
	mlx->textur.N_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_N, \
		&mlx->textur.N_img.x, &mlx->textur.N_img.y);
	mlx->textur.S_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_S, \
		&mlx->textur.S_img.x, &mlx->textur.S_img.y);
	mlx->textur.W_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_W, \
		&mlx->textur.W_img.x, &mlx->textur.W_img.y);
	mlx->textur.E_img.addr = (int *)mlx_get_data_addr(mlx->textur.E_img.img, \
	&mlx->textur.E_img.bits_per_pixel, \
		&mlx->textur.E_img.line_length, &mlx->textur.E_img.endian);
	mlx->textur.N_img.addr = (int *)mlx_get_data_addr(mlx->textur.N_img.img, \
	&mlx->textur.N_img.bits_per_pixel, \
	&mlx->textur.N_img.line_length, &mlx->textur.N_img.endian);
	mlx->textur.W_img.addr = (int *)mlx_get_data_addr(mlx->textur.W_img.img, \
	&mlx->textur.W_img.bits_per_pixel, \
		&mlx->textur.W_img.line_length, &mlx->textur.W_img.endian);
	mlx->textur.S_img.addr = (int *)mlx_get_data_addr(mlx->textur.S_img.img, \
	&mlx->textur.S_img.bits_per_pixel, \
		&mlx->textur.S_img.line_length, &mlx->textur.S_img.endian);
	free(mlx->info->path_E);
	free(mlx->info->path_N);
	free(mlx->info->path_W);
	free(mlx->info->path_S);
}

void	clear_draw(t_mlx **mlx)
{
	mlx_destroy_image((*mlx)->ptr, (*mlx)->data.img);
	mlx_clear_window((*mlx)->ptr, (*mlx)->win_ptr);
	(*mlx)->data.img = mlx_new_image((*mlx)->ptr, WIN_W, WIN_H);
	(*mlx)->data.addr = mlx_get_data_addr((*mlx)->data.img, \
	&(*mlx)->data.bits_per_pixel, \
	&(*mlx)->data.line_length, &(*mlx)->data.endian);
}
