/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmakhf <ielmakhf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:05:13 by ielmakhf          #+#    #+#             */
/*   Updated: 2023/03/05 22:54:59 by ielmakhf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSS_H
# define PARSS_H

# include "../42Get_next_line/get_next_line.h"
# include "../42Libft/libft.h"
# include "./struct.h"

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

////////////////////////////// Parss ////////////////////////////////

void	fill_data(char *av, t_map **head, t_map **head2);
void	search_map(t_info *info, t_map *head, t_map *head2, t_position *pos);
char	*get_filename_ext(char *filename);
void	error_handler(char *mssg, int exit_status);
void	check_path(char *path);
void	free_tab(char **tab);
int		check_digit(char *str);
void	lsttoarray(t_map *map, t_info *info);
int		ft_lstsize(t_map *lst);
void	free_stuff(t_info *info, t_map *head, t_map *head2);
size_t	get_longest_len(char **str);
int		check_line(char *line);
int		check_dup(t_map *elements, char *first_elements, int len);
char	*join_rest(char *str, int len);
int		check_colors(t_info *info, char **colors, int i_);
int		char_check(char ch, int *check);
void	lsttoarray2(t_map *map, t_info *info);
void	search_map_utils(t_info *info, int *check);
void	player_check(char **map_arr, int i, int j);
int		char_check(char ch, int *check);
int		check_elements_utils(t_info *info, t_map *list, char **elements);
int		get_direction(char **direction);
void	fill_list(t_map ***head2, t_map **cub, char *str);
void	fill_list2(t_map ***head, t_map **tmp, char *str);
int		skip_new_line(char **str, int fd);
int		check_file(char *av);
int		search_player(char p);
int		with_space(t_info *info, char **colors);
int		without_space(t_info *info, char **colors);
int		init_color(t_info *info, char **colors, char *tmp, int i);

/////////////////////// MLX //////////////////////////////

void	mini_map(t_mlx *mlx);
void	start_execution(t_info *info, t_position *pos, t_mlx *mlx);
void	draw(t_mlx *mlx);
void	xpm_image(t_mlx *mlx);

#endif