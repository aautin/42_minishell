/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:06:53 by aautin            #+#    #+#             */
/*   Updated: 2024/03/19 14:13:06 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETENV_H
# define GETENV_H

t_list	*create_env(char **envp);
char	*ft_getenv(t_list *envp, char *to_find);
void	remove_env(t_list **envp, t_list *head, char *to_find);
int		modify_env(t_list *envp, char *to_find, char *new_content);

#endif