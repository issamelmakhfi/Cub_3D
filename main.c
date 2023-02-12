/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/12 13:41:19 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void    miniMap(t_info *info, t_position *pos)
{
    (void)pos;
    void    *ptr;

    ptr = mlx_init();
    printf("%d %d\n" , info->map_w, info->map_h);
    mlx_new_window(ptr, info->map_w * CELL_SIZE, info->map_h * CELL_SIZE, "Cub3D");
    mlx_loop(ptr);
    
}

int main(int ac, char **av)
{
    t_info   *cub;
    t_position  *pos;
    int fd;

    fd = open("map.cub", O_RDONLY);
    cub = malloc(sizeof(t_info));
    pos = malloc(sizeof(t_position));
    if (ac != 2)
        return (1);
    if (!get_filename_ext(av[1]) || ft_strcmp(get_filename_ext(av[1]), ".cub"))
        error_handler("No such file or directory", 1);
    parss_map(av[1], cub, pos);
    miniMap(cub, pos);
    free (cub);
    free (pos);
    return (0);
}