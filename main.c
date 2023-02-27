/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/27 20:52:57 by ielmakhf         ###   ########.fr       */
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
	mlx->image.img = mlx_xpm_file_to_image(mlx->ptr, mlx->info->map->path_N, &mlx->image.x, &mlx->image.y);
	mlx->image.addr =(int*)mlx_get_data_addr(mlx->image.img, &mlx->image.bits_per_pixel, &mlx->image.line_length, &mlx->image.endian);
}

int get_texture_color (t_mlx *mlx, int x, int y)
{
    int a;
	if (x >= mlx->image.x - 1 || y >= mlx->image.y - 1 || x < 0 || y < 0)
		return (0);
    a = mlx->image.addr[y * mlx->image.x + x];
    return (a);
}

void	map3D(t_mlx *mlx)
{
	int	wallHeight =  0;
	int	topPixel;
	double dis;
	int i = 0;
	int j;
	int offset = 0;
	
	drawCell(mlx);
	xpm_image(mlx);
	while (i < N_RAY)
	{
		dis = mlx->rays[i].save_distance * mlx->table->cos_table[abs(N_RAY / 2 - i)];
		wallHeight = (WIN_H / dis) * CELL_SIZE;
		j = 0;
		if (mlx->rays[i].first == 'v')
			offset = (int)mlx->rays[i].y_save % CELL_SIZE * ((double)mlx->image.x / CELL_SIZE);
		else
			offset = (int)mlx->rays[i].x_save % CELL_SIZE * ((double)mlx->image.x / CELL_SIZE);
		if (((WIN_H - wallHeight) / 2) <= 0)
			j  = -1 * (((WIN_H - wallHeight) / 2));
		while (j < wallHeight)
		{
			int color = get_texture_color(mlx, offset, j * ((double)mlx->image.y / (double)wallHeight));
			topPixel = ((WIN_H - wallHeight) / 2) + j;
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