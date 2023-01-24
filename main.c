/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/24 14:37:41 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/parss.h"

// void leak()
// {
// 	system("leaks cub3D map.cub");
// }

int main(int ac, char **av)
{
    t_map   *map;
    
    map = malloc(sizeof(t_map));
    if (!map)
        return (1);
    if (ac != 2)
        return (1);
    if (ft_strcmp(get_filename_ext(av[1]), ".cub"))
        error_handler("Bad Map", 1);
    parss_map(map, av[1]);
    free (map);
    return (0);
}