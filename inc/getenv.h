/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/03/21 16:36:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_H
# define GETENV_H

#include "libft/libft.h"

t_list	*create_env(char **envp);
char	*ft_getenv(t_list *envp, const char to_find[]);
int		remove_env(t_list **envp, const char to_find[]);
int		modify_env(t_list *envp, const char key[], const char new_value[]);

#endif