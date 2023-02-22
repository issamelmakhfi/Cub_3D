/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCells.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:02 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/22 18:31:48 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Coordonates.h"

void    initPov(t_position *pos, char P)
{
    if (P == 'N')
        pos->pov = N;
    else if (P == 'S')
        pos->pov = S;
    else if (P == 'W')
        pos->pov = W;
    else if (P == 'E')
        pos->pov = E;
}

void    initData(t_info *info, t_position *pos)
{
    int i;
    int j;
    int idx;
    char    *str;

    i = 0;
    j = 0;
    idx = 0;
    str = "NSWE";
    while (info->map_arr[i])
    {
        j = 0;
        while (info->map_arr[i][j])
        {
            idx  = 0;
            while (str[idx])
            {
                if (info->map_arr[i][j] == str[idx])
                {
                    initPov(pos, str[idx]);
                    pos->x_cell = j;
                    pos->y_cell = i;
                }
                idx++;
            }
            j++;
        }
        i++;
    }
    info->map_h = i;
    info->map_w = getLongestLen(info->map_arr);
	if ((WIN_H / info->map_h) < (WIN_W / info->map_w))
		info->cell_size = WIN_H / info->map_h;
	else
		info->cell_size = WIN_W / info->map_w;
	info->cell_size = CELL_SIZE;
    pos->virtual_px = CELL_SIZE * (pos->x_cell + 0.5);
    pos->virtual_py = CELL_SIZE * (pos->y_cell + 0.5);
}