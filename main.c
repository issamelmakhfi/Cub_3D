/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/17 20:49:26 by ielmakhf         ###   ########.fr       */
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
	printf("%d %d\n", x1 , y1);
	dx = mlx->pos->virtual_px - x1;
	dy = mlx->pos->virtual_py - y1;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	
	X = mlx->pos->virtual_px;
	Y = mlx->pos->virtual_py;
	while (i <= steps)
	{
		my_mlx_pixel_put(&mlx->data, X, Y, RED);
		X += x_inc;
		Y += y_inc;
		i++;
	}
	// exit(1);
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
			x = i * cos(T) + mlx->pos->virtual_px;
			y = i * sin(T) + mlx->pos->virtual_py;
			my_mlx_pixel_put(&mlx->data, x, y, 0xFF0000);
			T++;
		}
		i++;
	}
	printf("%f %f\n", mlx->pos->virtual_px, mlx->pos->virtual_py);
	DDA(mlx, (sin(mlx->pos->rotationAngle) * 60) + mlx->pos->virtual_px, (cos(mlx->pos->rotationAngle) * 60) + mlx->pos->virtual_py);
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