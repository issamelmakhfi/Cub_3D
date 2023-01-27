/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/27 11:44:31 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"
#include <string.h>
#include <errno.h>

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

int check_colors(char **colors)
{
    int i = 1;
    char    *tmp;

    if (colors[0] && (!ft_strcmp(colors[0], "F") || !ft_strcmp(colors[0], "C")))
    {
        while (colors[i])
        {
            tmp = ft_strtrim(colors[i], ",");
            if (check_digit(tmp))
                return (1);
            if (ft_atoi(tmp) > 256)
                return (1);
            i++;
        }
    }
    else
        return (1);
    return (0);
}

int check_elements(t_map *map)
{
    int i;
    char **elements;

    i = 0;
    while (map->map_tab[i])
    {
        elements = ft_split(map->map_tab[i], ' ');
        if (ft_strlen(elements[0]) == 2)
        {
            if (get_direction(elements))
                return (1);
        }
        else if (ft_strlen(elements[0])  == 1)
        {
            if (check_colors(elements))
                return (1);
        }
        free_tab(elements);
        elements = NULL;
        i++;
    }
    return (0);
}

int map_check(t_map *map)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (map->map_tab[i])
    {
        j = 0;
        while (map->map_tab[0][j])
        {
            if (map->map_tab[i][j++] != '1')
                return (1);
        }
        tmp = ft_strtrim(map->map_tab[i], "1");
        j = 0;
        while (tmp[j])
        {
            if (tmp[j++] != '0')
                return (1);
        }
        i++;
    }
    return (0);
}

int parss_map(t_map *map, char *av)
{
    int fd;
    int i;
    char *str;

    i = 0;
    fd = open(av,  O_RDONLY);
    if (fd < 0)
        exit(1);
    while ((str = get_next_line(fd)))
    {
        map->map_tab[i] = malloc(1 * ft_strlen(str));
        map->map_tab[i] = str;
        i++;
    }
    map->map_tab[i] = NULL;
    if (check_elements(map))
        error_handler("ELEMENTS ERROR", 1);
    if (map_check(map))
        error_handler("MAP ERROR", 1);
    // free_tab(map->map_tab);
    return (0);
}