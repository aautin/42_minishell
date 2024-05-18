/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:59:27 by aautin            #+#    #+#             */
/*   Updated: 2024/05/18 20:26:28 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "libft/libft.h"

# define NOT_DOT	0
# define ONE_DOT	1
# define TWO_DOT	2

void	go_previous_dir(char **components, int twodot_index);
int		change_directory(t_list **envp, char absolute_path[]);
int		change_pwds(t_list **envp, char absolute_path[],
			t_list *pwd, t_list *oldpwd);
int		get_pathmode(char const arg[]);
int		is_directory(char const path[]);
char	*build_path(char const s1[], char const s2[],
			size_t const s1_len, size_t const s2_len);
char	*get_cdpath(char **cdpaths, char const arg[], size_t const arg_len);

#endif