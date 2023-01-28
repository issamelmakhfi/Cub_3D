/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:12:05 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/27 11:13:47 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"


void    check_path(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_handler("no such file or directory", 127);
}

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