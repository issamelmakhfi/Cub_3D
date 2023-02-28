/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/01 00:25:21 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * (-1));
}

void	DDA(t_mlx *mlx, int x1, int y1)
{
	int dx;
	int dy;
	int	steps;
	float x_inc;
	float y_inc;
	float X;
	float Y;
	int i;

	i = 0;
	dx = x1 - (mlx->pos->virtual_px * ((double)mlx->info->cell_sizeMap / CELL_SIZE));
	dy = y1 - (mlx->pos->virtual_py * ((double)mlx->info->cell_sizeMap / CELL_SIZE));
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;

	X = mlx->pos->virtual_px * ((double)mlx->info->cell_sizeMap / CELL_SIZE);
	Y = mlx->pos->virtual_py * ((double)mlx->info->cell_sizeMap / CELL_SIZE);
	while (i <= steps)
	{
		my_mlx_pixel_put(&mlx->data, X * mlx->pos->space, Y * mlx->pos->space, 0xFF0000);
		X += x_inc;
		Y += y_inc;
		i++;
	}
}

void	draw_player(t_mlx *mlx)
{
	double	T = 0;
	int x; 
	int y; 
	int i;

	x = mlx->pos->virtual_px * ((double)mlx->info->cell_sizeMap / CELL_SIZE);
	y = mlx->pos->virtual_py * ((double)mlx->info->cell_sizeMap / CELL_SIZE);

	i = 0;
	while (i < 5)
	{
		T=0;	
		while (T < 360)
		{
			x = i * mlx->table->cos_table[(int)(T / ANG_IN_D)] + (mlx->pos->virtual_px * ((double)mlx->info->cell_sizeMap / CELL_SIZE));
			y = i * mlx->table->sin_table[(int)(T / ANG_IN_D)] + (mlx->pos->virtual_py * ((double)mlx->info->cell_sizeMap / CELL_SIZE));
			my_mlx_pixel_put(&mlx->data, x * mlx->pos->space, y * mlx->pos->space, 0xFF0000);
			T++;
		}
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		DDA(mlx, mlx->rays[i].x_save * ((double)mlx->info->cell_sizeMap / CELL_SIZE), mlx->rays[i].y_save * ((double)mlx->info->cell_sizeMap / CELL_SIZE));
		i++;
	}
}

void    draw(t_mlx *mlx)
{
	int x;
	int y;
	
    x = mlx->x * mlx->info->cell_sizeMap;
    y = mlx->y * mlx->info->cell_sizeMap;
    int i = x;
    int j = y;


	
    while (j - y < mlx->info->cell_sizeMap - mlx->pos->b_cells)
    {
        i = x;
        while (i - x < mlx->info->cell_sizeMap - mlx->pos->b_cells)
        {
            my_mlx_pixel_put(&mlx->data, i * mlx->pos->space, j * mlx->pos->space, mlx->color);
            i++;
        }
        j++;
    }
}

void    miniMap(t_mlx *mlx)
{
	mlx->x = 0;
	mlx->y = 0;
	
    while (mlx->x < mlx->info->map_w)
    {
        mlx->y = 0;
        while (mlx->y < mlx->info->map_h)
        {
			if (mlx->info->map_arr[mlx->y][mlx->x] == '1')
	        	mlx->color = 0x000000;
            if (mlx->info->map_arr[mlx->y][mlx->x] == '0' || mlx->info->map_arr[mlx->y][mlx->x] == 'N')
                mlx->color = 0xFFFFFF;
			if (mlx->info->map_arr[mlx->y][mlx->x] == ' ')
			{
				mlx->y++;
				continue;
			}
			draw(mlx);
            mlx->y++;
        }
        mlx->x++;
    }
	draw_player(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
}

void	drawCell(t_mlx *mlx)
{
	mlx->x = 0;
	
	while (mlx->x < WIN_W)
	{
		mlx->y = 0;
		while (mlx->y < WIN_H / 2)
		{
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, 0xA300FF);
			mlx->y++;
		}
		mlx->x++;
	}
	mlx->x = 0;
	while (mlx->x < WIN_W)
	{
		mlx->y = WIN_H / 2;
		while (mlx->y < WIN_H)
		{
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, 0xC0C0C0);
			mlx->y++;
		}
		mlx->x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 216, 104);
}

void	xpm_image(t_mlx *mlx)
{
	mlx->textur.E_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_E ,&mlx->textur.E_img.x, &mlx->textur.E_img.y);
	mlx->textur.N_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_N ,&mlx->textur.N_img.x, &mlx->textur.N_img.y);
	mlx->textur.S_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_S ,&mlx->textur.S_img.x, &mlx->textur.S_img.y);
	mlx->textur.W_img.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->path_W ,&mlx->textur.W_img.x, &mlx->textur.W_img.y);
	
	mlx->textur.E_img.addr =(int*)mlx_get_data_addr(mlx->textur.E_img.img, &mlx->textur.E_img.bits_per_pixel, &mlx->textur.E_img.line_length, &mlx->textur.E_img.endian);
	mlx->textur.N_img.addr =(int*)mlx_get_data_addr(mlx->textur.N_img.img, &mlx->textur.N_img.bits_per_pixel, &mlx->textur.N_img.line_length, &mlx->textur.N_img.endian);
	mlx->textur.S_img.addr =(int*)mlx_get_data_addr(mlx->textur.S_img.img, &mlx->textur.S_img.bits_per_pixel, &mlx->textur.S_img.line_length, &mlx->textur.S_img.endian);
	mlx->textur.W_img.addr =(int*)mlx_get_data_addr(mlx->textur.W_img.img, &mlx->textur.W_img.bits_per_pixel, &mlx->textur.W_img.line_length, &mlx->textur.W_img.endian);
}

int	get_offset(int direction, int x, int y, int img_x)
{
	if (direction == 'v')
		return (y % CELL_SIZE * ((double)img_x / CELL_SIZE));
	else
		return (x % CELL_SIZE * ((double)img_x / CELL_SIZE));
}

int get_texture_color (t_mlx *mlx, int y, int i)
{
    int color = 0;
	t_image tmp_image;

	if (mlx->pos->povTextur == E)
		tmp_image = mlx->textur.E_img;
	if (mlx->pos->povTextur == N)
		tmp_image = mlx->textur.N_img;
	if (mlx->pos->povTextur == S)
		tmp_image = mlx->textur.S_img;
	if (mlx->pos->povTextur == W)
		tmp_image = mlx->textur.W_img;
	y *= (double)tmp_image.y / (double)mlx->pos->wallHeight;
	mlx->pos->offset = get_offset(mlx->rays[i].first , mlx->rays[i].x_save , mlx->rays[i].y_save, tmp_image.x);
	if (mlx->pos->offset >= tmp_image.x - 1 || y  >= tmp_image.y - 1 || mlx->pos->offset < 0 || y < 0)
		return (0);
	color = tmp_image.addr[y * tmp_image.x + mlx->pos->offset];
    return (color);
}

void	map3D(t_mlx *mlx)
{
	int	topPixel;
	double dis;
	int i = 0;
	int j;
	
	drawCell(mlx);
	xpm_image(mlx);
	while (i < N_RAY)
	{
		dis = mlx->rays[i].save_distance * mlx->table->cos_table[abs(N_RAY / 2 - i)];
		mlx->pos->wallHeight = (WIN_H / dis) * CELL_SIZE;
		j = 0;
		if (mlx->rays[i].first == 'v')
		{
			if (mlx->rays[i].ray_pov >= 0 && mlx->rays[i].ray_pov <= 180)
				mlx->pos->povTextur = E;
			if (mlx->rays[i].ray_pov >= 180 && mlx->rays[i].ray_pov <= 360)
				mlx->pos->povTextur = W;
		}
		else if (mlx->rays[i].first == 'h')
		{
			if ((mlx->rays[i].ray_pov >= 0 && mlx->rays[i].ray_pov <= 90) || (mlx->rays[i].ray_pov >= 270 && mlx->rays[i].ray_pov < 360))
				mlx->pos->povTextur = N;
			else
				mlx->pos->povTextur = S;
		}
		if (((WIN_H - mlx->pos->wallHeight) / 2) <= 0)
			j  = -1 * (((WIN_H - mlx->pos->wallHeight) / 2));
		while (j < mlx->pos->wallHeight)
		{
			int color = get_texture_color(mlx, j, i);
			topPixel = ((WIN_H - mlx->pos->wallHeight) / 2) + j;
			if (topPixel > WIN_H)
				break;
			my_mlx_pixel_put(&mlx->data , i, topPixel, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
}

int main(int ac, char **av)
{
    t_info   *info;
    t_position  *pos;
    t_mlx		*mlx;
	t_map   *head = NULL;
	t_map   *Chead = NULL;

    info = malloc(sizeof(t_info));
    pos = malloc(sizeof(t_position));
    mlx = malloc(sizeof(t_mlx));
    if (ac != 2)
        return (1);
    if (!get_filename_ext(av[1]) || ft_strcmp(get_filename_ext(av[1]), ".cub"))
        error_handler("No such file or directory", 1);
    fill_data(av[1], &head, &Chead);
	searchMap(info, head, Chead, pos);
	start_execution(info, pos, mlx);

	free_stuff(info, head, Chead);
    free (info);
    free (pos);
	free(mlx);
    return (0);
}