/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:39 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/11 18:57:55 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

void    free_stuff(t_info *info, t_map *head, t_map *Chead)
{
    free_tab(info->map_arr);
    free(info);
    while (head)
    {
        free(head->map_tab);
        free(head);
        head = head->next;
    }
    while (Chead)
    {
        free(Chead->elements);
        free(Chead);
        Chead = Chead->next;
    }
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

int checkLine(char *line)
{
    int i;

    i = 0;
    if (!line[0])
        return (1);
    while (line[i])
    {
        if (!ft_isdigit(line[i]))
        {
            if (line[i] == 'P' || line[i] == ' ')
            {
                i++;
                continue;
            }
            else
                return (1);
        }
        i++;
    }
    return (0);
}

int checkDup(t_map *elements, char  *first_elements, int len)
{
    t_map *tmp;
    int check = 0;

    tmp = elements;
    while (tmp)
    {
        // printf("%s\n", tmp->elements);
        if (!ft_strncmp(tmp->elements, first_elements, len))
            check++;
        tmp = tmp->next;
    }
    if (check != 1)
        return (1);
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