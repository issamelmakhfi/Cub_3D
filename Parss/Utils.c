/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:12:05 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/25 20:14:32 by ielmakhf         ###   ########.fr       */
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