/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCells.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:02 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/28 14:37:19 by ielmakhf         ###   ########.fr       */
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
	char	**tmp;

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
		info->cell_sizeMap = WIN_H / info->map_h;
	else
		info->cell_sizeMap = WIN_W / info->map_w;
	info->cell_size = CELL_SIZE;
    pos->virtual_px = info->cell_size * (pos->x_cell + 0.5);
    pos->virtual_py = info->cell_size * (pos->y_cell + 0.5);
	pos->map_px = info->cell_sizeMap * (pos->x_cell + 0.5);
	pos->map_py = info->cell_sizeMap * (pos->y_cell + 0.5);
	pos->space = 0.3;
	pos->b_cells = info->cell_sizeMap * 0.1;
	i = 0;
	while (info->elements[i])
	{
		tmp = ft_split(info->elements[i], ' ');
		if (!ft_strncmp(tmp[0], "NO", 2))
			info->path_N = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "SO", 2))
			info->path_S = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "WE", 2))
			info->path_W = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "EA", 2))
			info->path_E = ft_strdup(tmp[1]);
		free_tab(tmp);
		i++;
	}
}
