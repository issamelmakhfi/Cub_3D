/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:20:33 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 18:41:25 by ielmakhf         ###   ########.fr       */
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
	mlx->textur.e_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_e, \
		&mlx->textur.e_img.x, &mlx->textur.e_img.y);
	mlx->textur.n_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_n, \
		&mlx->textur.n_img.x, &mlx->textur.n_img.y);
	mlx->textur.s_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_s, \
		&mlx->textur.s_img.x, &mlx->textur.s_img.y);
	mlx->textur.w_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_w, \
		&mlx->textur.w_img.x, &mlx->textur.w_img.y);
	mlx->textur.e_img.addr = (int *)mlx_get_data_addr(mlx->textur.e_img.img, \
	&mlx->textur.e_img.bits_per_pixel, \
		&mlx->textur.e_img.line_length, &mlx->textur.e_img.endian);
	mlx->textur.n_img.addr = (int *)mlx_get_data_addr(mlx->textur.n_img.img, \
	&mlx->textur.n_img.bits_per_pixel, \
	&mlx->textur.n_img.line_length, &mlx->textur.n_img.endian);
	mlx->textur.w_img.addr = (int *)mlx_get_data_addr(mlx->textur.w_img.img, \
	&mlx->textur.w_img.bits_per_pixel, \
		&mlx->textur.w_img.line_length, &mlx->textur.w_img.endian);
	mlx->textur.s_img.addr = (int *)mlx_get_data_addr(mlx->textur.s_img.img, \
	&mlx->textur.s_img.bits_per_pixel, \
		&mlx->textur.s_img.line_length, &mlx->textur.s_img.endian);
	free(mlx->info->path_e);
	free(mlx->info->path_n);
	free(mlx->info->path_w);
	free(mlx->info->path_s);
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
