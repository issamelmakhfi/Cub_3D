/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 01:09:03 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	draw_player(t_mlx *mlx)
{
	int		i;

	i = 0;
	draw_point(mlx);
	while (i < N_RAY)
	{
		dda(mlx, mlx->rays[i].x_save * mlx->pos->adapter, \
		mlx->rays[i].y_save * mlx->pos->adapter);
		i++;
	}
}

void	draw(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = mlx->x * mlx->info->cell_sizeMap;
	y = mlx->y * mlx->info->cell_sizeMap;
	i = x;
	j = y;
	while (j - y < mlx->info->cell_sizeMap - mlx->pos->b_cells)
	{
		i = x;
		while (i - x < mlx->info->cell_sizeMap - mlx->pos->b_cells)
		{
			my_mlx_pixel_put(&mlx->data, i * mlx->pos->space, j \
				* mlx->pos->space, mlx->color);
			i++;
		}
		j++;
	}
}

void	mini_map(t_mlx *mlx)
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
			if (mlx->info->map_arr[mlx->y][mlx->x] == '0' || \
				mlx->info->map_arr[mlx->y][mlx->x] == 'N')
				mlx->color = 0xFFFFFF;
			if (mlx->info->map_arr[mlx->y][mlx->x] == ' ' || \
				mlx->info->map_arr[mlx->y][mlx->x] == '2')
			{
				mlx->y++;
				continue ;
			}
			draw(mlx);
			mlx->y++;
		}
		mlx->x++;
	}
	draw_player(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
}

void	map_projection(t_mlx *mlx)
{
	int		i;

	i = 0;
	draw_cell(mlx);
	while (i < N_RAY)
	{
		mlx->pos->dis = mlx->rays[i].save_distance * \
			mlx->table->cos_table[abs(N_RAY / 2 - i)];
		mlx->pos->wallHeight = (WIN_H / mlx->pos->dis) * CELL_SIZE;
		get_pov(mlx, i);
		project_wall(mlx, i);
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->data.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_info		*info;
	t_position	*pos;
	t_mlx		*mlx;
	t_map		*head;
	t_map		*head2;

	head = NULL;
	head2 = NULL;
	info = malloc(sizeof(t_info));
	pos = malloc(sizeof(t_position));
	mlx = malloc(sizeof(t_mlx));
	if (ac != 2)
		return (1);
	if (!get_filename_ext(av[1]) || ft_strcmp(get_filename_ext(av[1]), ".cub"))
		error_handler("No such file or directory", 1);
	fill_data(av[1], &head, &head2);
	searchMap(info, head, head2, pos);
	start_execution(info, pos, mlx);
	free_stuff(info, head, head2);
	free (pos);
	free(mlx);
	return (0);
}
