/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/04/13 16:06:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_H
# define GETENV_H

# include "libft/libft.h"

void	ft_remove(t_list **head, t_list *prev, t_list *cur);
int		modify(t_list *envp, const char key[], const char new_value[]);
t_list	*create_env(char **envp);
char	*ft_getenv(t_list *envp, const char to_find[]);

#endif