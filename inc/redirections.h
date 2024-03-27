/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/27 18:38:04 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "libft/libft.h"

int	redirect_fd(int oldfd, int newfd);
int	save_std_fd(int std_fd[3]);
int	reset_std_fd(int std_fd[3]);
int	apply_normal_redirections(t_list *current_token, t_list *last_token,
		t_list **current_here_doc, int last_exit_status);

#endif
