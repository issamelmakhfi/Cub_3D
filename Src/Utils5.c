/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:37:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/06 02:25:41 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	init_color(t_info *info, char **colors, char *tmp, int i)
{
	if (check_digit(tmp))
	{
		free(tmp);
		return (1);
	}
	if (ft_atoi(tmp) > 256)
	{
		free(tmp);
		return (1);
	}
	if (i == 1)
		info->r = ft_atoi(tmp);
	if (i == 2)
		info->g = ft_atoi(tmp);
	else
		info->b = ft_atoi(tmp);
	if (!ft_strcmp(colors[0], "C"))
		info->c_color = create_trgb(0, info->r, info->g, info->b);
	else
		info->f_color = create_trgb(0, info->r, info->g, info->b);
	return (free(tmp), 0);
}

int	check_colors(t_info *info, char **colors, int i_)
{
	if (colors[0] && (!ft_strcmp(colors[0], "F") || !ft_strcmp(colors[0], "C")))
	{
		if (i_ == 2 && without_space(info, colors))
			return (1);
		if (i_ == 4 && with_space(info, colors))
			return (1);
		if (!ft_strcmp(colors[0], "C"))
			info->c_color = create_trgb(0, info->r, info->g, info->b);
		else
			info->f_color = create_trgb(0, info->r, info->g, info->b);
	}
	else
		return (1);
	return (0);
}

int	get_direction(t_map *list, char **direction)
{
	char	*tmp;

	tmp = ft_substr(list->elements, 2, ft_strlen(list->elements));
	tmp = ft_strtrim(tmp, " ");
	if (direction[0] && !ft_strcmp(direction[0], "NO"))
		check_path(tmp);
	else if (direction[0] && !ft_strcmp(direction[0], "SO"))
		check_path(tmp);
	else if (direction[0] && !ft_strcmp(direction[0], "WE"))
		check_path(tmp);
	else if (direction[0] && !ft_strcmp(direction[0], "EA"))
		check_path(tmp);
	else
		return (1);
	return (0);
}
