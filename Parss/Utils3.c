/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:26:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 17:15:36 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	check_colors(t_info *info, char **colors)
{
	int		i;
	char	*tmp;
	int		r;
	int		g;
	int		b;

	i = 0;
	if (colors[0] && (!ft_strcmp(colors[0], "F") || !ft_strcmp(colors[0], "C")))
	{
		while (colors[++i])
		{
			tmp = ft_strtrim(colors[i], ",");
			if (check_digit(tmp))
			{
				free (tmp);
				return (1);
			}
			if (ft_atoi(tmp) > 256)
			{
				free(tmp);
				return (1);
			}
			if (i == 1)
				r = ft_atoi(tmp);
			if (i == 2)
				g = ft_atoi(tmp);
			else
				b = ft_atoi(tmp);
			free(tmp);
		}
		if (!ft_strcmp(colors[0], "C"))
			info->c_color = create_trgb(0, r, g, b);
		else
			info->f_color = create_trgb(0, r, g, b);
	}
	else
		return (1);
	return (0);
}

int	char_check(char ch, int *check)
{
	char	*str;
	char	*str1;
	int		i;

	i = 0;
	str1 = "NSWE";
	str = "102 ";
	while (str[i] && str1[i])
	{
		if (ch == str[i])
			return (0);
		if (ch == str1[i])
		{
			*check = *check + 1;
			if (*check > 1)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (1);
	}
	return (0);
}

void	search_map_utils(t_info *info, int *check)
{
	size_t	len;
	int		i;
	int		j;

	i = -1;
	len = get_longest_len(info->map_arr);
	while (info->map_arr[++i])
		info->map_arr[i] = join_rest(info->map_arr[i], len);
	i = -1;
	while (info->map_arr[++i])
	{
		j = -1;
		while (info->map_arr[i][++j])
		{
			if (char_check(info->map_arr[i][j], check))
				error_handler("MAP ERROR0", 1);
			if (info->map_arr[i][j] == ' ' || info->map_arr[i][j] == '2')
				player_check(info->map_arr, i, j);
		}
	}
}

int	check_elements_utils(t_info *info, t_map *list, char **elements)
{
	int	i;

	i = 0;
	if (elements[0] && ft_strlen(elements[0]) == 2)
	{
		while (elements[i])
			i++;
		if (i != 2 || get_direction(elements) || \
			check_dup(list, elements[0], 2))
			return (1);
	}
	else if (elements[0] && ft_strlen(elements[0]) == 1)
	{
		while (elements[i])
			i++;
		if (i != 4 || check_colors(info, elements) || \
			check_dup(list, elements[0], 1))
			return (1);
	}
	else
		return (1);
	return (0);
}
