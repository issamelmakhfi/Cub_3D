/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/26 20:17:09 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"
#include <string.h>
#include <errno.h>

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;        
    }
    free(tab);
}

char    *get_filename_ext(char *filename)
{
    char *ptr;

    ptr = ft_strchr(filename, '.');
    if (!ptr)
        return NULL;
    return (ptr);
}

int get_direction(char **direction)
{
    printf("HERE1\n");
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

int check_digit(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (!ft_isdigit(str[i++]))
            return (1);
    }
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
        if (get_direction(elements))
            return (1);
        if (check_colors(elements))
            return (1);
        free_tab(elements);
        elements = NULL;
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
    // check_colors(map);
    // free_tab(map->map_tab);
    return (0);
}