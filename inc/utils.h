/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:14:47 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/01 17:04:43 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft/libft.h"

char	*ask_input(char const prompt[]);
void	free_token(void *content);
void	my_perror(char const name[], char const msg[]);
int		add_to_list(t_list **list, void *content);
void	free_heredoc(void *content);

#endif
