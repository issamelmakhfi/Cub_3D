/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 21:46:12 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_player(t_data *img, t_info *info, t_mlx *mlx)
{
	(void)info;
	int	x = 0;
	int i = mlx->pos->virtual_px;
	int j = mlx->pos->virtual_py;

	while (x < 10)
	{
		printf("here\n");
		my_mlx_pixel_put(img, i, j, mlx->color);
		x++;
		i++;
		j++;
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
	        mlx->color = 0xFFFFFF;
            if (info->map_arr[mlx->y][mlx->x] == '0')
                mlx->color = 0x000000;
            if (pos->x_cell == mlx->x && pos->y_cell == mlx->y)
			{
				mlx->color = 0xFF0000;
				// draw_player(&mlx->data, info, mlx);
			}
			// else
			// {
				draw(&mlx->data, info, mlx);
			// }
            mlx->y++;
        }
        mlx->x++;
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
    int fd;

    fd = open("map.cub", O_RDONLY);
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