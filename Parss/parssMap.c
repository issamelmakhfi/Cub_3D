/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 23:09:29 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	check_elements(t_info *info, t_map *list_elements)
{
	int		i;
	t_map	*list;
	char	**elements;

	i = 0;
	list = list_elements;
	while (list)
	{
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
			error_handler("+++++++MAP ERROR1", 1);
		if (map_arr[i + 1])
		{
			if (map_arr[i + 1][j] == '0' || map_arr[i + 1][j] == str[idx])
				error_handler("+++++++MAP ERROR2", 1);
		}
		if (i && map_arr[i - 1][j])
		{
			if (map_arr[i - 1][j] == '0' || map_arr[i - 1][j] == str[idx])
				error_handler("+++++++MAP ERROR3", 1);
		}
		idx++;
	}
}

void	search_map(t_info *info, t_map *head, t_map *head2, t_position *pos)
{
	int		check;
	int		i;
	int		j;

	check = 0;
	i = -1;
	if (check_elements(info, head2))
		error_handler("ELEMENTS ERROR", 1);
	lsttoarray(head, info);
	lsttoarray2(head2, info);
	init_data(info, pos);
	search_map_utils(info, &check);
	if (!check)
		error_handler("NEED PLAYER", 1);
	while (info->map_arr[++i])
	{
		j = -1;
		while (info->map_arr[i][++j])
		{
			if (!search_player(info->map_arr[i][j]))
				info->map_arr[i][j] = '0';
		}
	}
}

void	fill_data2(char *str, t_map **head, t_map **head2, int fd)
{
	int		i;
	t_map	*tmp;
	t_map	*cub;

	i = 0;
	while (str)
	{
		if (i < 6)
		{
			if (!skip_new_line(&str, fd))
				continue ;
			fill_list(&head2, &cub, str);
			i++;
		}
		else
			fill_list2(&head, &tmp, str);
		free(str);
		str = get_next_line(fd);
	}
}

void	fill_data(char *av, t_map **head, t_map **head2)
{
	int		fd;
	char	*str;

	fd = check_file(av);
	str = get_next_line(fd);
	fill_data2(str, head, head2, fd);
}
