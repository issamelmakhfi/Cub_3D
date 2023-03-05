/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:39:11 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 21:19:40 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	fill_list(t_map ***head2, t_map **cub, char *str)
{
	if (!(**head2))
	{
		(*cub) = malloc(sizeof(t_map));
		**head2 = (*cub);
		(*cub)->elements = ft_strdup(str);
		(*cub)->next = NULL;
	}
	else
	{
		(*cub)->next = malloc(sizeof(t_map));
		(*cub) = (*cub)->next;
		(*cub)->elements = ft_strdup(str);
		(*cub)->next = NULL;
	}
}

void	fill_list2(t_map ***head, t_map **tmp, char *str)
{
	if (!(**head))
	{
		(*tmp) = malloc(sizeof(t_map));
		(**head) = (*tmp);
		(*tmp)->map_tab = ft_strdup(str);
		(*tmp)->next = NULL;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_map));
		(*tmp) = (*tmp)->next;
		(*tmp)->map_tab = ft_strdup(str);
		(*tmp)->next = NULL;
	}
}

int	skip_new_line(char **str, int fd)
{
	if (*str[0] == '\0')
	{
		free(*str);
		*str = get_next_line(fd);
		return (0);
	}
	return (1);
}

int	check_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		error_handler("No such file or directory", 1);
	return (fd);
}
