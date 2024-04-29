/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:11:52 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/29 19:36:12 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_EXEC_H
# define CHECK_EXEC_H

char	*check_exec(char const exec_name[], char *const *paths);
void	my_perror(char const name[], char const msg[]);
void	file_perror(char const name[]);

#endif
