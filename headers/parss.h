/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:05:13 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/28 19:40:52 by ielmakhf         ###   ########.fr       */
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

int parss_map(char *av);
char    *get_filename_ext(char *filename);
void    error_handler(char *mssg, int exit_status);
void    check_path(char *path);
void    free_tab(char **tab);
int check_digit(char *str);

#endif