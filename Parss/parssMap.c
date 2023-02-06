/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/06 16:17:08 by ielmakhf         ###   ########.fr       */
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
            {
                free (tmp);
                return (1);
            }
            if (ft_atoi(tmp) > 256)
            {
                free(tmp);
                return (1);
            }
            i++;
            free(tmp);
        }
    }
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
        elements = ft_split(list->elements, ' ');
        if (elements[0] && ft_strlen(elements[0]) == 2)
        {
            if (get_direction(elements))
                return (1);
        }
        else if (elements[0] && ft_strlen(elements[0])  == 1)
        {
            if (check_colors(elements))
                return (1);
        }
        free_tab(elements);
        elements = NULL;
        list = list->next;
    }
    return (0);
}

char    *join_rest(char *str, size_t len)
{
    char    *tmp;
    int s;
    size_t i;

    i = 0;
    tmp = malloc(sizeof(char) * len + 1);
    if (!tmp)
        return (NULL);
    s = 0;
    while (i < len)
    {
        if (i < ft_strlen(str))
            tmp[i] = str[i];
        else
            tmp[i] = '2';
        i++;
    }
    tmp[i] = '\0';
    i = 0;
    while (tmp[i] == ' ')
    {
        tmp[i] = '2';
        i++;
    }
    i = 0;
    free(str);
    return (tmp);
}

size_t  getLongestLen(char **str)
{
    int i;
    size_t  len;

    i = 0;
    len = 0;
    while (str[i])
    {
        if (len < ft_strlen(str[i]))
            len = ft_strlen(str[i]);
        i++;
    }
    return (len);
}

void    fill_map(t_info *info)
{
    int i;
    int j;
    size_t len;

    i = 0;
    j = 0;
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
            if (info->map_arr[i][j] == ' ' || info->map_arr[i][j] == '2')
            {
                if (info->map_arr[i][j + 1] == '0' || info->map_arr[i][j - 1] == '0' || info->map_arr[i][j - 1] == 'P' || info->map_arr[i][j + 1] == 'P')
                    error_handler("MAP ERROR", 1);
                else if (info->map_arr[i + 1])
                {
                    if (info->map_arr[i + 1][j] == '0'|| info->map_arr[i + 1][j] == 'P')
                        error_handler("MAP ERROR", 1);
                }
                if (i && info->map_arr[i - 1][j])
                {
                    if (info->map_arr[i - 1][j] == '0' || info->map_arr[i - 1][j] == 'P')
                        error_handler("MAP ERROR", 1);
                }
            }
            j++;
        }
        i++;
    }
}

int parss_map(char *av)
{
    int fd;
    char *str;
    t_info  *info;
    int len = 0;
    t_map *tmp = NULL, *head = NULL;
    t_map *cub = NULL, *Chead = NULL;

    info = malloc(sizeof(info));
    if (!info)
        return 1;
    fd = open(av,  O_RDONLY);
    if (fd < 0)
        error_handler("No such file or directory", 1);
    str = get_next_line(fd);
    str = ft_strtrim(str, "\n");
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
    lsttoarray(head, info);
    // fill_map(info);
    free_stuff(info, head, Chead);
    return (0);
}
