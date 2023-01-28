/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/28 19:46:47 by ielmakhf         ###   ########.fr       */
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
    while (map)
    {
        elements = ft_split(map->elements, ' ');
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
        map = map->next;
    }
    return (0);
}


void leak()
{
	system("leaks cub3D");
}

int parss_map(char *av)
{
    int fd;
    char *str;
    int len = 0;
    t_map *tmp = NULL, *head = NULL;
    t_map *cub = NULL, *Chead = NULL;

    fd = open(av,  O_RDONLY);
    if (fd < 0)
        exit(1);
    str = get_next_line(fd);
    while (str)
    {
        len = ft_strlen(str);
        if ((str[0] == '1'  || str[0] == ' ') && (str[len - 1] == '1' || str[len - 1] == ' '))
        {
            if (!head) {
                head = tmp = malloc(sizeof(t_map));
                tmp->map_tab = strdup(str);
                tmp->next = NULL;
            } else {
                tmp->next = malloc(sizeof(t_map));
                tmp = tmp->next;
                tmp->map_tab = strdup(str);
                tmp->next = NULL;
            }
        }
        else
        {
            if (!Chead) {
                Chead = cub = malloc(sizeof(t_map));
                cub->elements = strdup(str);
                cub->next = NULL;
            } else {
                cub->next = malloc(sizeof(t_map));
                cub = cub->next;
                cub->elements = strdup(str);
                cub->next = NULL;
            }
        }
        free(str);
        str = get_next_line(fd);
    }
    if (check_elements(Chead))
        error_handler("ELEMENTS ERROR", 1);
    while (head)
    {
        free(head->map_tab);
        free(head);
        head = head->next;
    }
    // need to make pionter for Chead to free all of it 
    while (Chead)
    {
        free(Chead->elements);
        free(Chead);
        Chead = Chead->next;
    }
    while (1);
    return (0);
}