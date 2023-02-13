/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 12:05:22 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw(int x, int y, t_data *img, t_info *info, t_mlx *mlx)
{
    x *= info->cell_size;
    y *= info->cell_size;
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
    t_data  img;
    (void)pos;
    int x = 0;
    int y = 0;
    int idx = 0;
	int k = 0;

    mlx->ptr = mlx_init();
    img.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
    mlx->win_ptr = mlx_new_window(mlx->ptr, WIN_W, WIN_H, "Cub3D");
	mlx->color = 0xFFFFFF;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (x < info->map_w)
    {
        y = 0;
        while (y < info->map_h)
        {
	        mlx->color = 0xFFFFFF;
            if (info->map_arr[y][x] == '0')
                mlx->color = 0x000000;
            if (info->map_arr[y][x] == 'N')
                mlx->color = 0xFF0000;
            draw(x, y, &img, info, mlx);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, img.img, k, idx);
    mlx_loop(mlx->ptr);
    
}

int main(int ac, char **av)
{
    t_info   *info;
    t_position  *pos;
    t_mlx		*mlx;
    int fd;

    fd = open("map.cub", O_RDONLY);
    info = malloc(sizeof(t_info));
    pos = malloc(sizeof(t_position));
    mlx = malloc(sizeof(t_mlx));
    if (ac != 2)
        return (1);
    if (!get_filename_ext(av[1]) || ft_strcmp(get_filename_ext(av[1]), ".cub"))
        error_handler("No such file or directory", 1);
    parss_map(av[1], info, pos, mlx);

    // miniMap(info, pos, mlx);
    free (info);
    free (pos);
	free(mlx);
    return (0);
}