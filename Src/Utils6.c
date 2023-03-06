/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:40:00 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 23:50:52 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	without_space(t_info *info, char **colors)
{
	char	**str;
	int		idx;

	str = NULL;
	idx = 0;
	str = ft_split(colors[1], ',');
	while (str[idx])
	{
		if (init_color(info, colors, str[idx], idx + 1))
			return (1);
		idx++;
	}
	free(str);
	return (0);
}

int	with_space(t_info *info, char **colors)
{
	int		i;
	char	*tmp;

	i = 1;
	while (colors[i])
	{
		tmp = ft_strtrim(colors[i], ",");
		if (init_color(info, colors, tmp, i))
			return (1);
		i++;
	}
	return (0);
}

int	search_player(char p)
{
	char	*str;
	int		t;

	str = "NSWE";
	t = 0;
	while (str[t])
	{
		if (p == str[t])
			return (0);
		t++;
	}
	return (1);
}
