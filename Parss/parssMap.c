/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/10 00:57:05 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

int get_direction(char **direction, t_map *list)
{
    if (direction[0] && !ft_strcmp(direction[0], "NO") && !list->check)
    {
        check_path(direction[1], list);
    }
    else if (direction[0] && !ft_strcmp(direction[0], "SO"))
    {
        check_path(direction[1], list);
    }
    else if (direction[0] && !ft_strcmp(direction[0], "WE"))
        check_path(direction[1], list);
    else if (direction[0] && !ft_strcmp(direction[0], "EA"))
        check_path(direction[1], list);
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

int checkDup(t_map *elements, char  *first_elements, int len)
{
    t_map *tmp;
    int check = 0;

    tmp = elements;
    while (tmp)
    {
        if (!ft_strncmp(tmp->elements, first_elements, len))
            check++;
        tmp = tmp->next;
    }
    if (check > 1)
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
            if (i != 2 || get_direction(elements, list) || checkDup(list, elements[0], 2))
                return (1);
        }
        else if (elements[0] && ft_strlen(elements[0])  == 1)
        {
            while (elements[i])
                i++;
            if (i != 4 || check_colors(elements) || checkDup(list, elements[0], 1))
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

int charachtersCHeck(char ch, int *check)
{
    char    *str;
    char    *str1;
    int i;
    
    i = 0;
    str1 = "NSWE";
    str = "102 ";
    while (str[i] && str1[i])
    {
        if (ch == str[i])
            return (0);
        if (ch == str1[i])
        {
            *check = *check + 1;
            if (*check > 1)
                return (1);
            return (0);
        }
        i++;
    }
    return (1);
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

void    fill_map(t_info *info)
{
    int i;
    int j;
    size_t len;
    int check = 0;

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
            if (charachtersCHeck(info->map_arr[i][j], &check))
            {
                printf("%s\n", info->map_arr[i]);
                printf("%c\n", info->map_arr[i][j]);
                error_handler("MAP ERROR0", 1);
            }
            if (info->map_arr[i][j] == ' ' || info->map_arr[i][j] == '2')
            {
                player_check(info->map_arr, i, j);
                // if ((j > 0) && (info->map_arr[i][j + 1] == '0' || info->map_arr[i][j - 1] == '0' || info->map_arr[i][j - 1] == 'P' || info->map_arr[i][j + 1] == 'P'))
                //     error_handler("MAP ERROR1", 1);
                // if (info->map_arr[i + 1])
                // {
                //     if (info->map_arr[i + 1][j] == '0'|| info->map_arr[i + 1][j] == 'P')
                //         error_handler("MAP ERROR2", 1);
                // }
                // if (i && info->map_arr[i - 1][j])
                // {
                //     if (info->map_arr[i - 1][j] == '0' || info->map_arr[i - 1][j] == 'P')
                //         error_handler("MAP ERROR3", 1);
                // }
            }
            j++;
        }
        i++;
    }
    if (!check)
        error_handler("NEED PLAYER", 1);
        

}

int parss_map(char *av)
{
    int fd;
    char *str;
    t_info  *info;
    t_map *tmp = NULL, *head = NULL;
    t_map *cub = NULL, *Chead = NULL;

    info = malloc(sizeof(info));
    if (!info)
        return 1;
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
        free(str);
        str = get_next_line(fd);
    }
    if (check_elements(Chead))
        error_handler("ELEMENTS ERROR", 1);
    lsttoarray(head, info);
    // i = 0;
    // while (info->map_arr[i])
    //     printf("%s\n", info->map_arr[i++]);
    fill_map(info);
    free_stuff(info, head, Chead);
    return (0);
}
