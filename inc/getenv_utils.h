/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/03/21 16:36:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_UTILS_H
# define GETENV_UTILS_H

#include "libft/libft.h"

void	ft_remove(t_list **head, t_list *prev, t_list *cur);
int		modify(t_list *envp, const char key[], const char new_value[]);

#endif