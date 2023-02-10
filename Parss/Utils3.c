/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:26:10 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/10 16:27:01 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

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
