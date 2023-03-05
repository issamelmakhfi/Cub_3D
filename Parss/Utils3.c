/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:26:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 20:10:18 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
		if (ch == '\n')
			return (1);
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

void	seperate_map_check(t_info *info)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (info->map_arr[len])
		len++;
	while (info->map_arr[i])
	{
		if (info->map_arr[i][0] != '\0')
		{
			if (i + 1 < len && info->map_arr[i + 1][0] == '\0')
				error_handler("+++++++MAP ERROR_", 1);
		}
		i++;
	}
}

void	search_map_utils(t_info *info, int *check)
{
	size_t	len;
	int		i;
	int		j;

	i = -1;
	len = get_longest_len(info->map_arr);
	seperate_map_check(info);
	while (info->map_arr[++i])
		info->map_arr[i] = join_rest(info->map_arr[i], len);
	i = -1;
	while (info->map_arr[++i])
	{
		j = -1;
		while (info->map_arr[i][++j])
		{
			if (char_check(info->map_arr[i][j], check))
				error_handler("+++++++MAP ERROR", 1);
			if (info->map_arr[i][j] == ' ' || info->map_arr[i][j] == '2')
				player_check(info->map_arr, i, j);
		}
	}
}

int	check_elements_utils(t_info *info, t_map *list, char **elements)
{
	int		i;

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
		if (check_colors(info, elements, i) || \
			check_dup(list, elements[0], 1))
			return (1);
	}
	else
		return (1);
	return (0);
}
