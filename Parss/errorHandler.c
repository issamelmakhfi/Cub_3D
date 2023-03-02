/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorHandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:54:04 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 01:08:10 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

void	error_handler(char *mssg, int exit_status)
{
	ft_putendl_fd(mssg, 2);
	exit(exit_status);
}
