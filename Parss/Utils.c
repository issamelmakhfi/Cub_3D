/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:12:05 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 01:05:48 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handler("no such file or directory", 127);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_filename_ext(char *filename)
{
	char	*ptr;

	ptr = ft_strchr(filename, '.');
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	lsttoarray(t_map *map, t_info *info)
{
	t_map	*list;
	int		i;

	i = 0;
	list = map;
	info->map_arr = malloc(sizeof(char *) * ft_lstsize(list) + 1);
	if (!info->map_arr)
		return ;
	while (list)
	{
		(info->map_arr)[i++] = ft_strdup(list->map_tab);
		list = list->next;
	}
	info->map_arr[i] = NULL;
}

void	lsttoarray2(t_map *map, t_info *info)
{
	t_map	*list;
	int		i;

	i = 0;
	list = map;
	info->elements = malloc(sizeof(char *) * ft_lstsize(list) + 1);
	if (!info->elements)
		return ;
	while (list)
	{
		info->elements[i++] = ft_strdup(list->elements);
		list = list->next;
	}
	info->elements[i] = NULL;
}
