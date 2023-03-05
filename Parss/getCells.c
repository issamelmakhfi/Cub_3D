/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCells.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:02 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 15:53:41 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/drawing.h"

void	init_pov(t_position *pos, char P)
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

void	fill_elements(t_info *info)
{
	int		i;
	char	**tmp;

	i = 0;
	while (info->elements[i])
	{
		tmp = ft_split(info->elements[i], ' ');
		if (!ft_strncmp(tmp[0], "NO", 2))
			info->path_n = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "SO", 2))
			info->path_s = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "WE", 2))
			info->path_w = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "EA", 2))
			info->path_e = ft_strdup(tmp[1]);
		free_tab(tmp);
		i++;
	}
}

void	search_pov(t_info *info, t_position *pos)
{
	int		i;
	int		j;
	int		idx;
	char	*str;

	i = -1;
	str = "NSWE";
	while (info->map_arr[++i])
	{
		j = -1;
		while (info->map_arr[i][++j])
		{
			idx = -1;
			while (str[++idx])
			{
				if (info->map_arr[i][j] == str[idx])
				{
					init_pov(pos, str[idx]);
					pos->x_cell = j;
					pos->y_cell = i;
				}
			}
		}
	}
	info->map_h = i;
}

void	init_data(t_info *info, t_position *pos)
{
	search_pov(info, pos);
	info->map_w = get_longest_len(info->map_arr);
	if ((WIN_H / info->map_h) < (WIN_W / info->map_w))
		info->cell_size_map = WIN_H / info->map_h;
	else
		info->cell_size_map = WIN_W / info->map_w;
	info->cell_size = CELL_SIZE;
	pos->adapter = (double)info->cell_size_map / CELL_SIZE;
	pos->virtual_px = info->cell_size * (pos->x_cell + 0.5);
	pos->virtual_py = info->cell_size * (pos->y_cell + 0.5);
	pos->map_px = info->cell_size_map * (pos->x_cell + 0.5);
	pos->map_py = info->cell_size_map * (pos->y_cell + 0.5);
	pos->space = 0.4;
	pos->b_cells = info->cell_size_map * 1;
	pos->left_arrow = 0;
	pos->right_arrow = 0;
	pos->_a = 0;
	pos->_d = 0;
	pos->_s = 0;
	pos->_w = 0;
	pos->mini_map_ = 0;
	pos->old_x = WIN_W / 2;
	fill_elements(info);
}
