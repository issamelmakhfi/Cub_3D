/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 16:50:11 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	get_direction(char **direction)
{
	if (direction[0] && !ft_strcmp(direction[0], "NO"))
		check_path(direction[1]);
	else if (direction[0] && !ft_strcmp(direction[0], "SO"))
		check_path(direction[1]);
	else if (direction[0] && !ft_strcmp(direction[0], "WE"))
		check_path(direction[1]);
	else if (direction[0] && !ft_strcmp(direction[0], "EA"))
		check_path(direction[1]);
	else
		return (1);
	return (0);
}

int	check_elements(t_info *info, t_map *list_elements)
{
	int		i;
	t_map	*list;
	char	**elements;

	i = 0;
	list = list_elements;
	while (list)
	{
		list->check = 0;
		elements = ft_split(list->elements, ' ');
		if (check_elements_utils(info, list, elements))
			return (1);
		free_tab(elements);
		elements = NULL;
		list = list->next;
	}
	return (0);
}

void	player_check(char **map_arr, int i, int j)
{
	char	*str;
	int		idx;

	str = "NSWE";
	idx = 0;
	while (str[idx])
	{
		if ((j > 0) && (map_arr[i][j + 1] == '0' || map_arr[i][j - 1] == '0' || \
		map_arr[i][j - 1] == str[idx] || map_arr[i][j + 1] == str[idx]))
			error_handler("MAP ERROR1", 1);
		if (map_arr[i + 1])
		{
			if (map_arr[i + 1][j] == '0' || map_arr[i + 1][j] == 'P')
				error_handler("MAP ERROR2", 1);
		}
		if (i && map_arr[i - 1][j])
		{
			if (map_arr[i - 1][j] == '0' || map_arr[i - 1][j] == 'P')
				error_handler("MAP ERROR3", 1);
		}
		idx++;
	}
}

void	search_map(t_info *info, t_map *head, t_map *head2, t_position *pos)
{
	int		check;

	check = 0;
	if (check_elements(info, head2))
		error_handler("ELEMENTS ERROR", 1);
	lsttoarray(head, info);
	lsttoarray2(head2, info);
	init_data(info, pos);
	search_map_utils(info, &check);
	if (!check)
		error_handler("NEED PLAYER", 1);
}

void	fill_data(char *av, t_map **head, t_map **head2)
{
	int		fd;
	char	*str;
	t_map	*tmp;
	t_map	*cub;
	int		i;

	i = -1;
	fd = check_file(av);
	str = get_next_line(fd);
	while (str)
	{
		if (++i < 7)
		{
			if (!skip_new_line(&str, fd))
				continue ;
			fill_list(&head2, &cub, str);
		}
		else
		{
			if (!skip_new_line(&str, fd))
				continue ;
			fill_list2(&head, &tmp, str);
		}
		free(str);
		str = get_next_line(fd);
	}
}
