/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/04/28 17:37:36 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_UTILS_H
# define GETENV_UTILS_H

# include "libft/libft.h"

void	remove_env(t_list **head, t_list *prev, t_list *cur);
int		modify_env(t_list *envp, const char key[], const char new_value[]);
int		add_env(t_list **envp, char const key[], char const value[]);

#endif