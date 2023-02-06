/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:49:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/06 16:18:28 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/parss.h"

int main(int ac, char **av)
{
    t_info   *cub;
    
    cub = malloc(sizeof(t_info));
    if (!cub)
        return (1);
    if (ac != 2)
        return (1);
    if (ft_strcmp(get_filename_ext(av[1]), ".cub"))
        error_handler("Bad Map", 1);
    parss_map(av[1]);
    free (cub);
    while (1);
    return (0);
}