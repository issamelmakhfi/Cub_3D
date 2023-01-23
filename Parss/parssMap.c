/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:40:07 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/23 17:59:17 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

int parss_map(char *av)
{
    int fd;

    fd = open(av,  O_RDONLY);
    if (fd < 0)
        exit(1);
    printf("LOL\n");
    return (0);
}