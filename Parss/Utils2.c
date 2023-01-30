/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:39 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/01/30 21:51:23 by ielmakhf         ###   ########.fr       */
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