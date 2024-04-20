/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/04/20 19:28:38 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_H
# define GETENV_H

# include "libft/libft.h"

void	remove_env(t_list **head, t_list *prev, t_list *cur);
int		modify_env(t_list *envp, const char key[], const char new_value[]);
int		add_env(t_list **envp, char const key[], char const value[]);
t_list	*create_env(char **envp);
char	*ft_getenv(t_list *envp, char const to_find[]);

#endif