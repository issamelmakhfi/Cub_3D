/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/25 20:17:25 by ielmakhf         ###   ########.fr       */
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
    // int fd;

    if (direction[0] && !ft_strcmp(direction[0], "NO"))
        check_path(direction[1]);
    else if (direction[0] && !ft_strcmp(direction[0], "SO"))
        check_path(direction[1]);
    else if (direction[0] && !ft_strcmp(direction[0], "WE"))
        check_path(direction[1]);
    else if (direction[0] && !ft_strcmp(direction[0], "EA"))
        check_path(direction[1]);
    else
        return (2);    
    return (0);
}

int check_directions(t_map *map)
{
    int i;
    char **dire;

    i = 0;
    while (map->map_tab[i])
    {
        dire = ft_split(map->map_tab[i], ' ');
        if (get_direction(dire) == 1)
            return (1);
        free_tab(dire);
        dire = NULL;
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
    check_directions(map);
    // free_tab(map->map_tab);
    return (0);
}