/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:05:13 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/02/06 20:13:44 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSS_H
#define PARSS_H

#include "../42Get_next_line/get_next_line.h"
#include "../42Libft/libft.h"
#include "./struct.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int     parss_map(char *av);
char    *get_filename_ext(char *filename);
void    error_handler(char *mssg, int exit_status);
void    check_path(char *path);
void    free_tab(char **tab);
int     check_digit(char *str);
void    lsttoarray(t_map *map, t_info *info);
int     ft_lstsize(t_map *lst);
void    free_stuff(t_info *info, t_map *head, t_map *Chead);
size_t  getLongestLen(char **str);
int     checkLine(char *line);

#endif