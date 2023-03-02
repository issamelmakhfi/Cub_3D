/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:50:39 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/02 01:06:02 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parss.h"

void	free_stuff(t_info *info, t_map *head, t_map *head2)
{
	free_tab(info->map_arr);
	while (head)
	{
		free(head->map_tab);
		free(head);
		head = head->next;
	}
	while (head2)
	{
		free(head2->elements);
		free(head2);
		head2 = head2->next;
	}
	free(info);
}

size_t	get_longest_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (len < ft_strlen(str[i]))
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	check_dup(t_map *elements, char *first_elements, int len)
{
	t_map	*tmp;
	int		check;

	tmp = elements;
	check = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->elements, first_elements, len))
			check++;
		tmp = tmp->next;
	}
	if (check != 1)
		return (1);
	return (0);
}

char	*join_rest(char *str, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		if (i < ft_strlen(str))
			tmp[i] = str[i];
		else
			tmp[i] = '2';
		i++;
	}
	tmp[i] = '\0';
	i = 0;
	while (tmp[i] == ' ')
	{
		tmp[i] = '2';
		i++;
	}
	i = 0;
	free(str);
	return (tmp);
}

int	ft_lstsize(t_map *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
