/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:14:47 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:33:55 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*ask_input(char const prompt[]);
void	free_token(void *content);
void	my_perror(char const name[], char const msg[]);

#endif
