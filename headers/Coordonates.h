/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coordonates.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:07:45 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/17 13:05:19 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORDONATES_H
#define COORDONATES_H

#include "../42Get_next_line/get_next_line.h"
#include "../42Libft/libft.h"
#include "cub3d.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void    initData(t_info *info, t_position *pos);
int	keey_move(int code, t_mlx *mlx);
void clear_draw(t_mlx **mlx);

#endif