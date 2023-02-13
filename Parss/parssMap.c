/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/13 15:48:35 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int get_direction(char **direction)
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

int check_elements(t_map *list_elements)
{
    int i;
    t_map   *list;
    char **elements;

    i = 0;
    list = list_elements;
    while (list)
    {
        list->check = 0;
        elements = ft_split(list->elements, ' ');
        if (elements[0] && ft_strlen(elements[0]) == 2)
        {
            
            while (elements[i])
                i++;
            if (i != 2 || get_direction(elements) || checkDup(list, elements[0], 2))
                return (1);
        }
        else if (elements[0] && ft_strlen(elements[0])  == 1)
        {
            while (elements[i])
                i++;
            if (i != 4 || check_colors(elements) || checkDup(list, elements[0], 1))
                return (1);
        }
        else
            return (1);
        free_tab(elements);
        elements = NULL;
        list = list->next;
    }
    return (0);
}

void player_check(char **map_arr, int i, int j)
{
    char *str;

    int     idx = 0;

    str = "NSWE";
    while (str[idx])
    {
        if ((j > 0) && (map_arr[i][j + 1] == '0' || map_arr[i][j - 1] == '0' || map_arr[i][j - 1] == str[idx] || map_arr[i][j + 1] == str[idx]))
            error_handler("MAP ERROR1", 1);
        if (map_arr[i + 1])
        {
            if (map_arr[i + 1][j] == '0'|| map_arr[i + 1][j] == 'P')
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

void    searchMap(t_info *info, t_map *head, t_map *Chead, t_position *pos)
{
    int i;
    int j;
    size_t len;
    int check;

    i = 0;
    j = 0;
    check = 0;
	if (check_elements(Chead))
        error_handler("ELEMENTS ERROR", 1);
    lsttoarray(head, info);
	initData(info, pos);
    len = getLongestLen(info->map_arr);
    while (info->map_arr[i])
    {
        info->map_arr[i] = join_rest(info->map_arr[i], len);
        i++;
    }
    i = 0;
    while (info->map_arr[i])
    {
        j = 0;
        while (info->map_arr[i][j])
        {
            if (charachtersCHeck(info->map_arr[i][j], &check))
                error_handler("MAP ERROR0", 1);
            if (info->map_arr[i][j] == ' ' || info->map_arr[i][j] == '2')
                player_check(info->map_arr, i, j);
            j++;
        }
        i++;
    }
    if (!check)
        error_handler("NEED PLAYER", 1);

}

void	fill_data(char *av, t_map **head, t_map **Chead)
{
    int fd;
    char *str;
    t_map   *tmp = NULL; 
    t_map   *cub = NULL;

    fd = open(av,  O_RDONLY);
    if (fd < 0)
        error_handler("No such file or directory", 1);
    str = get_next_line(fd);
    int i = 0;
    while (str)
    {
        if (i < 6)
        {
            if (str[0] == '\0')
            {
                free(str);
                str = get_next_line(fd);
                continue;
            }
            if (!(*Chead)) {
                (*Chead) = cub = malloc(sizeof(t_map));
                cub->elements = strdup(str);
                cub->next = NULL;
            } else {
                cub->next = malloc(sizeof(t_map));
                cub = cub->next;
                cub->elements = strdup(str);
                cub->next = NULL;
            }
            i++;
        }
        else
        {
            if (!str[0])
            {
                free(str);
                str = get_next_line(fd);
                continue;
            }
            if (!(*head)) {
                (*head) = tmp = malloc(sizeof(t_map));
                tmp->map_tab = strdup(str);
                tmp->next = NULL;
            } else {
                tmp->next = malloc(sizeof(t_map));
                tmp = tmp->next;
                tmp->map_tab = strdup(str);
                tmp->next = NULL;
            }
        }
        free(str);
        str = get_next_line(fd);
    }
}
