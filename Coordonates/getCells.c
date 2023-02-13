/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCells.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:02 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 19:16:54 by ielmakhf         ###   ########.fr       */
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
    pos->virtual_px = (pos->x_cell - 0.5) * CELL_SIZE;
    pos->virtual_py = (pos->y_cell - 0.5) * CELL_SIZE;
    info->map_h = i;
    info->map_w = getLongestLen(info->map_arr);
}