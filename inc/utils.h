/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:14:47 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 16:19:15 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft/libft.h"

char	*ask_input(char const prompt[]);
void	free_token(void *content);
void	my_perror(char const name[], char const msg[]);
int		add_to_list(t_list **list, void *content);
void	free_here_doc(void *content);

#endif
