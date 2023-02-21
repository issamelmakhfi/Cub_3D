/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/21 18:47:55 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
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
	dx = x1 - mlx->pos->virtual_px;
	dy = y1 - mlx->pos->virtual_py;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc =  (dx / (float)steps);
	y_inc = dy / (float)steps;

	X = mlx->pos->virtual_px;
	Y = mlx->pos->virtual_py;
	float t = 0.9;
	while (i <= steps)
	{
		my_mlx_pixel_put(&mlx->data, X, Y, 0xFF0000);
		X += x_inc;
		Y += y_inc;
		t -= 0.05;
		if (Y < 0 || X < 0 || Y > WIN_H || X > WIN_W)
			break;
		i++;
	}
}

void	draw_player(t_mlx *mlx)
{
	double	T = 0;
	int x = mlx->pos->virtual_px;
	int y= mlx->pos->virtual_py;

	int i = 0;
	mlx->pos->rotationSpeed = 2;
	while (i < 5)
	{
		T=0;	
		while (T < 360)
		{
			x = i * mlx->table->cos_table[(int)(T / ANG_IN_D)] + mlx->pos->virtual_px;
			y = i * mlx->table->sin_table[(int)(T / ANG_IN_D)] + mlx->pos->virtual_py;
			my_mlx_pixel_put(&mlx->data, x, y, 0xFF0000);
			T++;
		}
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		DDA(mlx, mlx->rays[i].x_save , mlx->rays[i].y_save);
		i++;
	}
}

void    draw(t_data *img, t_info *info, t_mlx *mlx)
{
	int x;
	int y;
	
    x = mlx->x * info->cell_size;
    y = mlx->y * info->cell_size;
    int i = x;
    int j = y;


	
    while (j - y < info->cell_size - 1)
    {
        i = x;
        while (i - x < info->cell_size - 1)
        {
            my_mlx_pixel_put(img, i, j, mlx->color);
            i++;
        }
        j++;
    }
}

void    miniMap(t_info *info, t_position *pos, t_mlx *mlx)
{
    (void)pos;
	mlx->x = 0;
	mlx->y = 0;
	
    while (mlx->x < info->map_w)
    {
        mlx->y = 0;
        while (mlx->y < info->map_h)
        {
	        mlx->color = 0x000000;
            if (info->map_arr[mlx->y][mlx->x] == '0' || info->map_arr[mlx->y][mlx->x] == 'N')
                mlx->color = 0xFFFFFF;
			draw(&mlx->data, info, mlx);

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
			my_mlx_pixel_put(&mlx->data, mlx->x, mlx->y, 0xFFF000);
			mlx->y++;
		}
		mlx->x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
}

void	map3D(t_mlx *mlx)
{
	int	wallHeight=  0;
	int	topPixel;
	// int	bottomPixel;
	
	drawCell(mlx);
	int i = 0;
	int j = 0;
	while (i < N_RAY)
	{
		wallHeight = (WIN_H / mlx->rays[i].save_distance) * 8;
		j = 0;
		while (j < wallHeight)
		{
			topPixel = ((WIN_H - wallHeight) / 2) + j;
			if (topPixel > WIN_H)
			{
				printf("KOK\n");
				topPixel = WIN_H;
			}
			if (topPixel < 0)
			{
				ft_putendl_fd("HERE", 1);
			}
			my_mlx_pixel_put(&mlx->data , i, topPixel, 0xFFF3d4);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
	// drawFloor(mlx);
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