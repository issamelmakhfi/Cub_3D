/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:23 by Ma3ert            #+#    #+#             */
/*   Updated: 2023/02/18 15:52:22 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "parss.h"
# include "Coordonates.h"
#include "../minilibx/mlx.h"

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h> 
# include <math.h>

void		casting_rays(t_table *table, t_ray *rays, t_position position);
void		create_trigonometric_tables(int narc, t_table *table, int i);
void		send_ray(t_table *table, t_ray *ray, t_position position);
void		triangle_sides(t_ray *ray, t_position position, t_table *table);
void		calcul_cells(t_ray *ray);
void		check_skip(t_ray *ray, t_position position);
double		calcul_adjacent(double hypotenuse, double opposite);
double		calcul_opposite(double hypotenus, double adjacent);

#endif