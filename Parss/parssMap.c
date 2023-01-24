/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/24 17:21:16 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;        
    }
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
    int fd;
    
    if (!ft_strcmp(direction[0], "NO"))
    {
        fd = open(direction[1], O_RDONLY);
        if (fd < 0)
            return (1);
    }
    if (!ft_strcmp(direction[0], "SO"))
    {
        fd = open(direction[1], O_RDONLY);
        if (fd < 0)
            return (1);
    }
    if (!ft_strcmp(direction[0], "WE"))
    {
        
    }
    if ()
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
        if (!get_direction(dire))
        {
            printf("test\n");
            return 0;
        }
        i++;
    }
    return (1);
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
    free_tab(map->map_tab);
    return (0);
}